#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f

long long dp[25][25];
int split[25][25];
long long p[25];

void print_order(int i, int j) {
  if (i == j) {
    printf("M%d", i);
    return;
  }
  printf("(");
  print_order(i, split[i][j]);
  print_order(split[i][j] + 1, j);
  printf(")");
}

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i <= n; i++) {
    scanf("%lld", &p[i]);
  }

  // 初始化 dp[i][i] = 0
  for (int i = 1; i <= n; i++) {
    dp[i][i] = 0;
  }

  // 动态规划
  for (int len = 2; len <= n; len++) {
    for (int i = 1; i + len - 1 <= n; i++) {
      int j = i + len - 1;
      dp[i][j] = INF;

      for (int k = i; k < j; k++) {
        long long cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];

        // 如果更优则更新
        // 如果相等，优先选 k 最小（括号靠前）
        if (cost < dp[i][j]) {
          dp[i][j] = cost;
          split[i][j] = k;
        }
      }
    }
  }

  printf("%lld ", dp[1][n]);
  print_order(1, n);
  printf("\n");

  return 0;
}
