#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // abs
using namespace std;
using ll = long long;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end()); // 排序

    int mid = a[n / 2]; // 中位数
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += abs(a[i] - mid);
    }

    cout << sum << "\n";
    return 0;
}
