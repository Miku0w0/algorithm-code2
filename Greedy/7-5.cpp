#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 5;
const int inf = 0x3f3f3f3f;
const double M = sqrt(2) - 1;
int n, m, vis[N][N], sx, sy, ex, ey;
double s[N][N], dis[N][N], ans;
int ne[8][2] = {1, 0, -1, 0, 0, 1, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1};
struct node {
  int x, y;
} a, b, p;
int cross(node a, node b, node p) {
  return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}
void bfs() {
  memset(vis, 0, sizeof vis);
  // memset(dis, 0x5f, sizeof dis);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      dis[i][j] = inf;
  a = {sx, sy}, b = {ex, ey};
  dis[sx][sy] = s[sx][sy];
  queue<node> Q;
  Q.push(a);
  while (!Q.empty()) {
    int x = Q.front().x, y = Q.front().y;
    Q.pop();
    vis[x][y] = 0;
    for (int i = 0; i < 8; i++) {
      double w = 0;
      p.x = x + ne[i][0], p.y = y + ne[i][1];
      if (p.x < 0 || p.x >= n || p.y < 0 || p.y >= m)
        continue;
      if (cross(a, b, p) > 0 || p.x == ex && p.y == ey) {
        w = s[p.x][p.y];
        if (i > 3)
          w += (s[x][y] + s[p.x][p.y]) * M;
        if (dis[p.x][p.y] > dis[x][y] + w) {
          dis[p.x][p.y] = dis[x][y] + w;
          if (!vis[p.x][p.y]) {
            Q.push(p);
            vis[p.x][p.y] = 1;
          }
        }
      }
    }
  }
  ans += dis[ex][ey];
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> s[i][j];
  cin >> sy >> sx >> ey >> ex;
  ans = -s[sx][sy] - s[ex][ey];
  bfs();
  swap(ex, sx), swap(ey, sy);
  bfs();
  printf("%.2f", ans);
  return 0;
}