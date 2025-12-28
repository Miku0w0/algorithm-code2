#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// 全局变量
int N;                        // 集合A的元素个数
int Y;                        // 目标子集和
int T;                        // 待输出的第T个解
vector<int> A;                // 集合A的元素 (已排序)
vector<int> current_subset;   // 当前正在构建的子集
long long solution_count = 0; // 找到的解的数量
vector<int> result_solution;  // 存储第T个解

/**
 * 深度优先搜索/回溯函数
 * @param index 当前考虑的A数组元素的下标 (从0到N-1)
 * @param current_sum 当前子集元素的和
 */
void dfs(int index, int current_sum) {
  // 检查是否已经找到第 T 个解，如果是，则立即返回
  if (solution_count == T) {
    return;
  }

  // 终止条件 1：找到一个解
  if (current_sum == Y) {
    solution_count++;
    if (solution_count == T) {
      // 找到第 T 个解，记录并返回
      result_solution = current_subset;
    }
    return;
  }

  // 终止条件 2：所有元素都已考虑完
  if (index == N) {
    return;
  }

  // --------------------------------------------------------
  // 回溯搜索：对于 A[index]，有两种选择：
  // --------------------------------------------------------

  // A. 包含 A[index] (选择这个分支保证了字典序靠前)
  // 剪枝 1: 如果加上当前元素会超过目标和 Y，则停止
  if (current_sum + A[index] <= Y) {
    // 1. 做选择：将 A[index] 加入当前子集
    current_subset.push_back(A[index]);

    // 2. 递归：处理下一个元素 A[index+1]
    dfs(index + 1, current_sum + A[index]);

    // 3. 撤销选择 (回溯)：将 A[index] 从子集中移除
    // 无论是否找到解，都要回溯，为下一种选择做准备
    current_subset.pop_back();
  }

  // B. 不包含 A[index]
  // 继续递归，处理下一个元素 A[index+1]，和不变
  // (注意：这里不需要额外的剪枝，因为不选择 A[index]只会使和更小)
  // 必须确保在 'A' 分支的回溯后才执行此分支，保证搜索顺序
  dfs(index + 1, current_sum);
}

int main() {
  // 优化输入输出速度
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // 1. 读取 N, Y
  if (!(cin >> N >> Y)) {
    return 0;
  }

  // 2. 读取集合 A 的元素
  A.resize(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }

  // 3. 读取 T
  cin >> T;

  // 4. 从第一个元素 (下标 0) 开始进行回溯搜索
  dfs(0, 0);

  // 5. 输出结果
  if (solution_count == T) {
    // 找到了第 T 个解
    for (size_t i = 0; i < result_solution.size(); ++i) {
      cout << result_solution[i]
           << (i == result_solution.size() - 1 ? "" : " ");
    }
    cout << endl;
  } else {
    // 第 T 个解不存在
    cout << "No Solution!" << endl;
  }

  return 0;
}