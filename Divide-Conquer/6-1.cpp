#include <stdio.h>

int Power(int, int);

const int MOD = 10007;
int main() {
  int N, k;
  scanf("%d%d", &N, &k);
  printf("%d\n", Power(N, k));
  return 0;
}

/* Your function will be put here */
int Power(int a, int b) {
  int res = 1;
  a %= MOD; // 先取模
  while (b) {
    if (b & 1)
      res = res * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return res;
}