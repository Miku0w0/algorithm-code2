#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> y(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x >> y[i]; // 只关心 y 坐标
    }

    sort(y.begin(), y.end());
    int mid = y[n / 2]; // 中位数
    long long total = 0;
    for (int i = 0; i < n; i++)
        total += abs(y[i] - mid);

    cout << total << "\n";
    return 0;
}
