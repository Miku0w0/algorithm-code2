#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define inf 0x3f3f3f3f3f
using namespace std;
typedef pair<int, int> pa;
typedef long long ll;
int n, q;
ll ans;
int v[100005];
pa p[100005];
int tree[400005], lazy[400005];
bool cmp(const pa &a, const pa &b) {
  if (a.second == b.second)
    return a.first < b.first;
  return a.second < b.second;
}
void build(int l, int r, int t) {
  lazy[t] = 0;
  if (l == r)
    tree[t] = v[l];
  else {
    int mid = (l + r) >> 1;
    build(l, mid, t << 1);
    build(mid + 1, r, t << 1 | 1);
    tree[t] = min(tree[t << 1], tree[t << 1 | 1]);
  }
}
void pushdown(int t) {
  if (lazy[t] == 0)
    return;
  lazy[t << 1] += lazy[t];
  lazy[t << 1 | 1] += lazy[t];
  tree[t << 1] -= lazy[t];
  tree[t << 1 | 1] -= lazy[t];
  lazy[t] = 0;
}
void update(int l, int r, int t, int L, int R, int d) {
  if (l >= L && r <= R)
    tree[t] -= d, lazy[t] += d;
  else {
    pushdown(t);
    int mid = (l + r) >> 1;
    if (mid >= L)
      update(l, mid, t << 1, L, R, d);
    if (mid < R)
      update(mid + 1, r, t << 1 | 1, L, R, d);
    tree[t] = min(tree[t << 1], tree[t << 1 | 1]);
  }
}
ll query(int l, int r, int t, int L, int R) {
  if (l >= L && r <= R)
    return tree[t];
  if (l > R || r < L)
    return inf;
  int mid = (l + r) >> 1;
  ll d = inf;
  pushdown(t);
  if (mid >= L)
    d = min(d, query(l, mid, t << 1, L, R));
  if (mid < R)
    d = min(d, query(mid + 1, r, t << 1 | 1, L, R));
  tree[t] = min(tree[t << 1], tree[t << 1 | 1]);
  return d;
}
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n - 1; i++) {
    scanf("%d", &v[i]);
  }
  build(0, n - 2, 1);
  for (int i = 0; i < q; i++) {
    scanf("%d%d", &p[i].first, &p[i].second);
    if (p[i].first > p[i].second)
      swap(p[i].first, p[i].second);
    p[i].second--;
  }
  sort(p, p + q, cmp);
  for (int i = 0; i < q; i++) {
    ll d = query(0, n - 2, 1, p[i].first, p[i].second);
    ans += d;
    update(0, n - 2, 1, p[i].first, p[i].second, d);
  }
  printf("%lld", ans);
}
