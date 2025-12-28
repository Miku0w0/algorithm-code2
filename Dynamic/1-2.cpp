#include <stdio.h>

#define MAXM 50
#define MAXN 200

int profit[MAXM + 1][MAXN + 1];
int dp[MAXM + 1][MAXN + 1];
int choice[MAXM + 1][MAXN + 1];

int main() {
  int m, n;
  scanf("%d %d", &m, &n);

  // 输入 profit
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      scanf("%d", &profit[i][j]);
    }
  }

  // dp 初始化，事实上 dp[0][*] = 0
  for (int j = 0; j <= n; j++)
    dp[0][j] = 0;

  // DP 递推
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = -1;
      for (int k = 0; k <= j; k++) {
        int val = dp[i - 1][j - k] + profit[i][k];
        if (val > dp[i][j]) {
          dp[i][j] = val;
          choice[i][j] = k; // 商店 i 分配 k 人
        }
      }
    }
  }

  // 回溯求每个商店的分配人数
  int ansPeople[MAXM + 1];
  int remaining = n;

  for (int i = m; i >= 1; i--) {
    ansPeople[i] = choice[i][remaining];
    remaining -= ansPeople[i];
  }

  // 输出：注意题目要求商店编号从 m → 1 输出
  for (int i = m; i >= 1; i--) {
    printf("%d %d\n", i, ansPeople[i]);
  }

  // 最大利润
  printf("%d\n", dp[m][n]);

  return 0;
}
