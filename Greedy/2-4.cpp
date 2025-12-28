#include <bits/stdc++.h>
using namespace std;
int n, m;
map<int, int> q;
vector<int> a[1010];
double dis[2][1010];
struct node {
  int y;
  double sum;
} vis1[1010], vis2[1010];
bool cmp(node x, node y) // 排序
{
  if (x.sum == y.sum) {
    return abs(x.y) < abs(y.y);
  } else {
    return x.sum > y.sum;
  }
}
int trans(string c) // 字符串输入，并标记男生还是女生。
{
  int s = c.size();
  int sum = 0;
  if (c[0] == '-') {
    for (int i = 1; i < s; i++) {
      sum = sum * 10 + c[i] - '0';
    }
    q[sum] = 1;
  } else {
    for (int i = 0; i < s; i++) {
      sum = sum * 10 + c[i] - '0';
    }
  }
  return sum;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int k;
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      string c;
      cin >> c;
      // cout<<c<<endl;
      int x = trans(c);
      a[i].push_back(x); // vector存储照片信息
    }
  }

  string aa, bb;
  cin >> aa >> bb;
  int ax, bx;
  ax = trans(aa);
  bx = trans(bb);
  for (int i = 0; i < m; i++) // 统计A的与其他异性的亲密度
  {
    vector<int>::iterator it = find(a[i].begin(), a[i].end(), ax);
    if (it != a[i].end()) {
      for (int j = 0; j < a[i].size(); j++) {
        int y = a[i][j];
        int k = a[i].size();
        if (q[ax] != q[y]) {
          dis[0][y] += 1.0 / double(k);
        }
      }
    }
  }
  for (int i = 0; i < m; i++) // 统计B的与其他异性的亲密度；
  {
    vector<int>::iterator it = find(a[i].begin(), a[i].end(), bx);
    if (it != a[i].end()) {
      for (int j = 0; j < a[i].size(); j++) {
        int y = a[i][j];
        int k = a[i].size();
        if (q[bx] != q[y]) {
          dis[1][y] += 1.0 / double(k);
        }
      }
    }
  }
  int top1 = 0;
  int top2 = 0;
  for (int i = 0; i < n; i++) // 将A的亲密度的异性存储到结构体中便于排序
  {
    if (dis[0][i] != 0) {
      vis1[top1].y = i;
      vis1[top1].sum = dis[0][i];
      top1++;
    }
  }
  for (int i = 0; i < n; i++) // 将B的亲密度的异性存储到结构体中便于排序
  {
    if (dis[1][i] != 0) {
      vis2[top2].y = i;
      vis2[top2].sum = dis[1][i];
      top2++;
    }
  }
  sort(vis1, vis1 + top1, cmp);
  sort(vis2, vis2 + top2, cmp);
  int num1 = 0;
  int num2 = 0;
  double max1 = vis1[0].sum;
  double max2 = vis2[0].sum;
  int flag1 = 0;
  int flag2 = 0;
  for (int i = 1; i < top1;
       i++) // 判断A的亲密度最高的异性是否为B，统计A的最高亲密度异性有多少
  {
    if (max1 > vis1[i].sum) {
      break;
    }
    if (vis1[i].y == bx) {
      flag1 = 1;
    }
    num1 = i;
  }
  for (int i = 1; i < top2;
       i++) // 判断B的亲密度最高的异性是否为B，统计B的最高亲密度异性有多少
  {
    if (max2 > vis2[i].sum) {
      break;
    }
    if (vis2[i].y == ax) {
      flag2 = 1;
    }
    num2 = i;
  }
  /*for(int i=0;i<top1;i++)
  {
      cout<<ax<<" "<<vis1[i].y<<" "<<vis1[i].sum<<endl;
  }
  for(int i=0;i<top2;i++)
  {
      cout<<bx<<" "<<vis2[i].y<<" "<<vis2[i].sum<<endl;
  }*/
  if (top1 != 0 && top2 != 0) {
    if (flag1 == 1 && flag2 == 1) {
      if (q[ax] == 1 && q[bx] == 0) {
        printf("-%d %d\n", ax, bx);
      } else if (q[ax] == 0 && q[bx] == 1) {
        printf("%d -%d\n", ax, bx);
      }
    } else {
      for (int i = 0; i <= num1; i++) {
        if (q[ax] == 1) {
          printf("-%d %d\n", ax, vis1[i].y);
        } else {
          printf("%d -%d\n", ax, vis1[i].y);
        }
      }
      for (int i = 0; i <= num2; i++) {
        if (q[bx] == 1) {
          printf("-%d %d\n", bx, vis2[i].y);
        } else {
          printf("%d -%d\n", bx, vis2[i].y);
        }
      }
    }
  } else {
    if (q[ax] == 1 && q[bx] == 0) {
      printf("-%d %d\n", ax, bx);
    } else if (q[ax] == 0 && q[bx] == 1) {
      printf("%d -%d\n", ax, bx);
    }
  }
  return 0;
}