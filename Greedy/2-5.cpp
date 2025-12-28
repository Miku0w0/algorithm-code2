#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// ----------------------------------------------------------------------
// 1. 计算哈夫曼最小总长度 (L_min)
// ----------------------------------------------------------------------

/**
 * 结构体：用于哈夫曼树的节点
 */
struct HuffmanNode {
  int freq;
  // 默认构造函数，用于优先队列
  HuffmanNode(int f) : freq(f) {}
};

/**
 * 比较器：用于优先队列，频率小的优先级高 (最小堆)
 */
struct CompareNode {
  bool operator()(const HuffmanNode &a, const HuffmanNode &b) {
    return a.freq > b.freq;
  }
};

/**
 * 计算哈夫曼算法能达到的最小总编码长度 L_min
 * L_min 等于哈夫曼树所有非叶节点的频率之和。
 */
long long calculate_min_length(const vector<int> &freqs) {
  if (freqs.size() <= 1)
    return 0; // 只有一个或没有字符，总长度为0

  // 优先队列 (最小堆) 存储频率
  priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNode> pq;
  for (int f : freqs) {
    if (f > 0) { // 忽略频率为0的字符
      pq.push(HuffmanNode(f));
    }
  }

  long long min_length = 0;

  // 不断合并频率最小的两个节点
  while (pq.size() > 1) {
    // 取出频率最小的两个节点
    HuffmanNode node1 = pq.top();
    pq.pop();
    HuffmanNode node2 = pq.top();
    pq.pop();

    // 合并：新节点的频率等于两者之和
    int new_freq = node1.freq + node2.freq;

    // 关键：最小总长度 = 所有非叶节点频率之和
    min_length += new_freq;

    // 将新节点放回队列
    pq.push(HuffmanNode(new_freq));
  }

  return min_length;
}

// ----------------------------------------------------------------------
// 2. 检查前缀码 (Trie 树)
// ----------------------------------------------------------------------

/**
 * 结构体：Trie 树节点
 */
struct TrieNode {
  TrieNode *children[2] = {nullptr, nullptr}; // 0 和 1 两个分支
  bool is_end = false;                        // 是否有编码在此节点结束

  TrieNode() : is_end(false) {}
  ~TrieNode() {
    delete children[0];
    delete children[1];
  }
};

/**
 * 检查编码集是否为前缀码，并计算给定编码的总长度
 * @return true 如果是前缀码，否则 false
 */
bool is_prefix_code(const vector<pair<char, string>> &codes,
                    const map<char, int> &freqs, long long &given_length) {
  TrieNode *root = new TrieNode();
  given_length = 0;
  bool is_valid = true;

  for (const auto &p : codes) {
    char c = p.first;
    const string &code = p.second;

    // 计算给定长度
    if (freqs.count(c)) {
      given_length += (long long)freqs.at(c) * code.length();
    }

    // 插入Trie树并检查前缀码性质
    TrieNode *curr = root;
    for (char bit : code) {
      int index = bit - '0';

      // 检查情况 1：当前编码 C_i 是另一个编码 C_j 的前缀
      if (curr->is_end) {
        is_valid = false;
        break;
      }

      if (!curr->children[index]) {
        curr->children[index] = new TrieNode();
      }
      curr = curr->children[index];
    }

    if (!is_valid)
      break; // 跳出外层循环

    // 检查情况 2：当前编码 C_i 是另一个编码 C_j 的前缀
    // C_i 结束时，如果 curr 已经是叶子节点，则说明它已经被其他编码用作前缀
    if (curr->is_end || curr->children[0] || curr->children[1]) {
      is_valid = false;
    }

    curr->is_end = true;
  }

  // 释放内存
  delete root;
  return is_valid;
}

// ----------------------------------------------------------------------
// 3. 主函数
// ----------------------------------------------------------------------

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N; // 字符种类数
  if (!(cin >> N))
    return 0;

  // 存储字符频率
  map<char, int> freqs_map;
  vector<int> freqs_list;
  for (int i = 0; i < N; ++i) {
    char c;
    int f;
    cin >> c >> f;
    freqs_map[c] = f;
    freqs_list.push_back(f);
  }

  // 1. 计算最小总长度 L_min
  long long L_min = calculate_min_length(freqs_list);

  int M; // 待检编码套数
  cin >> M;

  // 2. 检查 M 套编码
  for (int m = 0; m < M; ++m) {
    vector<pair<char, string>> current_codes(N);
    for (int i = 0; i < N; ++i) {
      cin >> current_codes[i].first >> current_codes[i].second;
    }

    long long L_given = 0;

    // A. 前缀码检查
    bool is_prefix = is_prefix_code(current_codes, freqs_map, L_given);

    if (!is_prefix) {
      cout << "No\n";
      continue;
    }

    // B. 最优长度检查
    if (L_given == L_min) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return 0;
}