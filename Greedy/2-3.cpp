#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// 定义边的结构体
struct Edge {
  int u, v; // 连通的两个城镇编号
  int cost; // 改建的预算成本

  // 重载小于运算符，用于排序：按成本从小到大排序
  bool operator<(const Edge &other) const { return cost < other.cost; }
};

// 并查集（Disjoint Set Union, DSU）的实现
vector<int> parent; // 存储每个元素的父节点

// 查找根节点（带路径压缩）
int find_root(int i) {
  if (parent[i] == i) {
    return i;
  }
  // 路径压缩：直接指向根节点
  return parent[i] = find_root(parent[i]);
}

// 合并两个集合 (按秩合并/简单合并皆可)
// 返回 true 如果成功合并了两个不同的集合，否则返回 false
bool union_sets(int i, int j) {
  int root_i = find_root(i);
  int root_j = find_root(j);

  if (root_i != root_j) {
    // 合并：将其中一个根节点指向另一个根节点
    parent[root_j] = root_i;
    return true;
  }
  return false; // 已经在同一个集合中
}

int main() {
  // 优化输入输出速度
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M; // 城镇数目 N, 候选道路数目 M
  if (!(cin >> N >> M)) {
    return 0;
  }

  // 1. 读取所有边
  vector<Edge> edges(M);
  for (int i = 0; i < M; ++i) {
    cin >> edges[i].u >> edges[i].v >> edges[i].cost;
  }

  // 2. Kruskal 算法的第一步：按成本从小到大排序
  sort(edges.begin(), edges.end());

  // 3. 初始化并查集
  parent.resize(N + 1); // 城镇编号从 1 到 N
  iota(parent.begin(), parent.end(),
       0); // parent[i] = i (每个城镇的根节点是自己)

  long long min_cost = 0;
  int edges_count = 0; // 最小生成树中边的数量

  // 4. 遍历排序后的边，构建 MST
  for (const auto &edge : edges) {
    // 如果加入该边不会形成环 (即两端点不在同一个连通分量中)
    if (union_sets(edge.u, edge.v)) {
      min_cost += edge.cost;
      edges_count++;
    }

    // 剪枝：如果已经选择了 N-1 条边，则 MST 已经构建完成
    if (edges_count == N - 1) {
      break;
    }
  }

  // 5. 连通性判断
  // 只有当选择了 N-1 条边时，才能保证所有 N 个城镇是连通的。
  if (edges_count == N - 1) {
    cout << min_cost << endl;
  } else {
    // 边数不足 N-1，说明图不连通
    cout << "Impossible" << endl;
  }

  return 0;
}