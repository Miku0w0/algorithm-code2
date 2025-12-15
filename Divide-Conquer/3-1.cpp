#include <iostream>
#include <set>
using namespace std;
using ll = long long;
const int N = 2e5 + 9;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    multiset<ll> mst;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        mst.insert(x); // 使用非去重的multiset
    }
    bool first = true; // 控制空格
    for (auto val : mst)
    {
        if (!first)
            cout << ' ';
        cout << val;
        first = false;
    }
}