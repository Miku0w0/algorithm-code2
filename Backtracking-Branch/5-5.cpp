#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
int N, M;
int arr[100005];      // 存储折线点的高度值
int vi[100005] = {0}; // 表示纸片是否访问过
vector<int> ve[105];  // vector数组用来存放纸片的多个折线点高度
vector<int> vv;       // 容器用来存放已经找到位置的纸片
bool flag = true;
void DFS(int i) {     // 深度优先
  if (vv.size() == M) // 所有的纸片都有了对应的位置
  {
    flag = false;
    return;
  }
  if (!flag)
    return;
  for (int j = 1; j <= M; j++) {
    bool bo = true;
    if (vi[j] == 1)
      continue; // 该纸片已经找到位置
    if (ve[j][0] == arr[i]) {
      for (int k = 0; k < ve[j].size();
           k++) // 判断该段是否符合纸片与纸的折线点高度一一对应
      {
        if (ve[j][k] != arr[i + k]) {
          bo = false;
          break;
        }
      }
      if (bo) {
        vi[j] = 1;
        vv.push_back(j); // 满足条件的纸片放入容器
        DFS(i + ve[j].size() -
            1); // 很重要的-1，所有的纸片的折线点高度比纸的折线点高度要多，因为要满足相邻两纸片之间的相邻折线处高度相同
        if (!flag)
          return; // 纸的高度的数量=纸片高度的数量-纸片个数，表示纸片两两相邻
        vi[j] = 0;
        vv.pop_back();
      }
    }
  }
}
int main() {
  int a, b;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }
  cin >> M;
  for (int i = 1; i <= M; i++) {
    cin >> b;
    for (int j = 0; j < b; j++) {
      cin >> a;
      ve[i].push_back(a);
    }
  }
  DFS(1);
  cout << vv[0];
  for (int i = 1; i < vv.size(); i++) // 循环输出
  {
    cout << " " << vv[i];
  }
  cout << endl;
  return 0;
}