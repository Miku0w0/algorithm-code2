#include <algorithm>
#include <array> // 使用 std::array 替代 vector 存储 Move，以减少内存开销
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int MAX_N = 1000;
const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// 候选移动结构体：{行, 列, 度数, 距离平方, 方向索引}
using Move = array<int, 5>;

// 栈帧结构体：只存储当前步和下一步尝试的方向数组
struct StackFrame {
  int r, c;     // 当前马位置
  int step;     // 当前步数
  int next_idx; // 下一个要尝试的移动在 sorted_directions 中的索引
  // 优化：moves 列表只在计算时使用，栈帧中只保留排序后的方向索引
  array<int, 8> sorted_directions; // 存储 8 个方向的索引 (0-7)，按启发式排序
  int move_count;                  // 实际有多少个有效移动 (< 8)
};

// --- 辅助函数 (保持不变) ---
inline bool is_valid(int r, int c, int n, const vector<vector<int>> &board) {
  return r >= 0 && r < n && c >= 0 && c < n && board[r][c] == 0;
}

int get_degree(int r, int c, int n, const vector<vector<int>> &board) {
  int count = 0;
  for (int i = 0; i < 8; ++i) {
    if (is_valid(r + dx[i], c + dy[i], n, board)) {
      count++;
    }
  }
  return count;
}

inline int dist_from_center_sq(int r, int c, int center_r, int center_c) {
  int dr = r - center_r;
  int dc = c - center_c;
  return dr * dr + dc * dc;
}

// **优化：生成排序后的方向索引**
void get_sorted_directions(int r, int c, int center_r, int center_c, int n,
                           const vector<vector<int>> &board,
                           array<int, 8> &directions, int &count) {
  vector<Move> moves;
  for (int i = 0; i < 8; ++i) {
    int nr = r + dx[i];
    int nc = c + dy[i];
    if (is_valid(nr, nc, n, board)) {
      int deg = get_degree(nr, nc, n, board);
      int dist = dist_from_center_sq(nr, nc, center_r, center_c);
      // Move: {nr, nc, deg, dist, direction_index}
      moves.push_back({nr, nc, deg, dist, i});
    }
  }

  // 三级启发式排序
  sort(moves.begin(), moves.end(), [](const Move &a, const Move &b) {
    if (a[2] != b[2])
      return a[2] < b[2]; // 1. 度数小的优先
    if (a[3] != b[3])
      return a[3] > b[3]; // 2. 距离中心远的优先
    if (a[0] != b[0])
      return a[0] < b[0]; // 3. 行号小的优先
    return a[1] < b[1];   // 4. 列号小的优先
  });

  // 存储排序后的方向索引到栈帧的 array 中
  count = moves.size();
  for (int i = 0; i < count; ++i) {
    directions[i] = moves[i][4]; // moves[i][4] 存储了方向索引 (0-7)
  }
}

// **核心修改：非递归回溯 DFS (内存优化)**
bool iterative_dfs(int start_r, int start_c, int center_r, int center_c, int n,
                   vector<vector<int>> &board) {

  stack<StackFrame> s;
  const int total_cells = n * n;

  // 1. 初始化起点
  board[start_r][start_c] = 1;
  array<int, 8> initial_directions;
  int initial_count;
  get_sorted_directions(start_r, start_c, center_r, center_c, n, board,
                        initial_directions, initial_count);
  s.push({start_r, start_c, 1, 0, initial_directions, initial_count});

  while (!s.empty()) {
    StackFrame &current = s.top();
    int r = current.r;
    int c = current.c;
    int step = current.step;

    // 检查是否找到解
    if (step == total_cells) {
      for (int i = 0; i < 8; ++i) {
        if (r + dx[i] == center_r && c + dy[i] == center_c) {
          return true;
        }
      }
      // 不是封闭周游，需要回溯
    }

    // 尝试下一步
    if (current.next_idx < current.move_count) {
      int direction_idx = current.sorted_directions[current.next_idx];
      current.next_idx++;

      int nr = r + dx[direction_idx];
      int nc = c + dy[direction_idx];

      // 前进
      board[nr][nc] = step + 1;

      // 压入新的栈帧，计算下一位置的候选移动
      array<int, 8> next_directions;
      int next_count;
      get_sorted_directions(nr, nc, center_r, center_c, n, board,
                            next_directions, next_count);

      s.push({nr, nc, step + 1, 0, next_directions, next_count});
    } else {
      // 撤销和弹出
      board[r][c] = 0;
      s.pop();
    }
  }

  return false;
}

void adjust_board(int actual_start_r, int actual_start_c, int n,
                  vector<vector<int>> &board) {
  int actual_val = board[actual_start_r][actual_start_c];
  if (actual_val == 0)
    return;

  int total = n * n;
  int offset = actual_val - 1;

  vector<vector<int>> temp = board;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      board[i][j] = (temp[i][j] - offset - 1 + total) % total + 1;
    }
  }
}

void print_board(int n, const vector<vector<int>> &board) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << board[i][j];
      if (j < n - 1)
        cout << " ";
    }
    cout << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, a, b;
  if (!(cin >> n >> a >> b))
    return 1;

  int actual_start_r = a - 1;
  int actual_start_c = b - 1;

  // N 的最大值限制在这里
  if (n < 8 || n > MAX_N || actual_start_r < 0 || actual_start_r >= n ||
      actual_start_c < 0 || actual_start_c >= n) {
    return 1;
  }

  int center_r = (n - 1) / 2;
  int center_c = (n - 1) / 2;

  // board 可能会占用大量内存，但这是不可避免的
  vector<vector<int>> board(n, vector<int>(n, 0));

  bool found = iterative_dfs(center_r, center_c, center_r, center_c, n, board);

  if (found) {
    adjust_board(actual_start_r, actual_start_c, n, board);
    print_board(n, board);
  } else {
    return 1;
  }

  return 0;
}