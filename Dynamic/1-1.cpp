#include <stdio.h>
#include <string.h>

#define MAXN 2005

int dp[MAXN][MAXN];
char A[MAXN], B[MAXN];

int min(int a, int b) { return a < b ? a : b; }

int main() {
  scanf("%s", A);
  scanf("%s", B);

  int n = strlen(A);
  int m = strlen(B);

  // dp[i][j] 表示 A[0..i-1] 到 B[0..j-1] 的编辑距离
  for (int i = 0; i <= n; i++)
    dp[i][0] = i; // 删除 i 个
  for (int j = 0; j <= m; j++)
    dp[0][j] = j; // 插入 j 个

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (A[i - 1] == B[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1]; // 不需要修改
      } else {
        dp[i][j] = min(min(dp[i - 1][j] + 1,  // 删除
                           dp[i][j - 1] + 1), // 插入
                       dp[i - 1][j - 1] + 1   // 替换
        );
      }
    }
  }

  printf("%d\n", dp[n][m]);
  return 0;
}
