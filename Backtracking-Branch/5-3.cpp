#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// 全局变量
int N;                          // 人数/工作数 (1 <= N <= 20)
vector<vector<int>> Cost;       // 费用矩阵 Cost[i][j]：第i个人做工作j的费用
vector<bool> Used;              // Used[j]：记录工作 j 是否已被分配
long long min_cost = LLONG_MAX; // 存储找到的最小总费用，初始化为最大值

/**
 * 深度优先搜索/回溯函数，为第 person_id 个人分配工作
 * @param person_id 当前正在分配工作的人的编号 (0 到 N-1)
 * @param current_cost 当前累积的总费用
 */
void dfs(int person_id, long long current_cost) {

  // 1. 剪枝 (Pruning):
  // 如果当前费用已经大于或等于已找到的最小费用，则这条路径不可能更优
  if (current_cost >= min_cost) {
    return;
  }

  // 2. 终止条件：所有 N 个人都分配了工作
  if (person_id == N) {
    // 找到一个合法解，更新全局最小费用
    min_cost = min(min_cost, current_cost);
    return;
  }

  // 3. 回溯搜索：为当前人 (person_id) 尝试分配所有未分配的工作
  for (int job_id = 0; job_id < N; ++job_id) {
    // 检查工作 job_id 是否已被分配
    if (!Used[job_id]) {
      // A. 做选择：分配工作 job_id 给 person_id
      Used[job_id] = true;

      // B. 递归：处理下一个人 (person_id + 1)
      // 费用累加 Cost[person_id][job_id]
      dfs(person_id + 1, current_cost + Cost[person_id][job_id]);

      // C. 撤销选择 (回溯)：取消对工作 job_id 的标记
      Used[job_id] = false;
    }
  }
}

int main() {
  // 优化输入输出速度
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // 1. 读取 N
  if (!(cin >> N)) {
    return 0;
  }

  // 2. 初始化数据结构
  Cost.resize(N, vector<int>(N));
  Used.resize(N, false);

  // 3. 读取费用矩阵
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> Cost[i][j];
    }
  }

  // 4. 从第 0 个人开始分配工作，初始费用为 0
  dfs(0, 0);

  // 5. 输出最终结果
  cout << min_cost << endl;

  return 0;
}