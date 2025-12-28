#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// 全局变量用于存储图的结构和着色状态
int N, M, K;
// 邻接矩阵：Adj[i][j] = 1 表示结点 i 和 j 之间有边
int Adj[21][21] = {0}; 
// 颜色数组：Color[i] 存储结点 i 当前的颜色 (1到K)，0 表示未着色
int Color[21] = {0}; 

// 用于存储合法解的总数
long long solution_count = 0;

/**
 * 检查尝试将颜色 c 赋给结点 u 是否合法。
 * 只有当 u 的所有已着色的邻居都没有使用颜色 c 时才合法。
 */
bool is_safe(int u, int c) {
    // 遍历 u 的所有邻居 v (v 从 1 到 N)
    for (int v = 1; v <= N; ++v) {
        // 检查是否存在边 (u, v)
        if (Adj[u][v] == 1) {
            // 如果邻居 v 已经着色，且颜色与 c 相同
            if (Color[v] == c) {
                return false; // 不合法
            }
        }
    }
    return true; // 合法
}

/**
 * 深度优先搜索/回溯函数，对结点 u 进行着色
 * @param u 当前正在尝试着色的结点编号 (1 到 N)
 */
void dfs(int u) {
    // 终止条件：如果所有 N 个结点都已着色 (u 已经超过 N)
    if (u > N) {
        // 找到了一个合法的着色方案
        solution_count++;
        return; // 返回，继续回溯
    }

    // 尝试 K 种颜色 (颜色编号从 1 到 K)
    for (int c = 1; c <= K; ++c) {
        // 剪枝/检查：只有当颜色 c 对结点 u 合法时，才继续
        if (is_safe(u, c)) {
            // 1. 做选择：为结点 u 着色
            Color[u] = c;

            // 2. 递归：尝试为下一个结点 u+1 着色
            dfs(u + 1);

            // 3. 撤销选择 (回溯)：
            // 重置结点 u 的颜色为未着色 (0)，以便尝试下一个颜色 c'
            Color[u] = 0; 
        }
    }
    // 如果循环结束，说明结点 u 尝试了所有 K 种颜色都没有找到可行的路径，
    // 或者所有可行的路径都已探索完毕，自动回溯到上一个结点。
}

int main() {
    // 优化输入输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 读取 N, M, K
    if (!(cin >> N >> M >> K)) {
        return 0;
    }

    // 2. 读取 M 条边，构建邻接矩阵
    for (int i = 0; i < M; ++i) {
        int u, v;
        if (!(cin >> u >> v)) break;
        // 无向图，对称设置
        Adj[u][v] = 1;
        Adj[v][u] = 1;
    }

    // 3. 从第一个结点 (编号 1) 开始进行回溯搜索
    dfs(1);

    // 4. 输出最终的解数目
    cout << solution_count << endl;

    return 0;
}