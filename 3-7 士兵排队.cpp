#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }

    // 处理y坐标：直接找中位数
    sort(y.begin(), y.end());
    int y_median = y[n / 2];

    // 处理x坐标：先排序，然后计算x[i] - i
    sort(x.begin(), x.end());
    vector<int> adjusted_x(n);
    for (int i = 0; i < n; i++)
    {
        adjusted_x[i] = x[i] - i;
    }

    // 找到调整后的x坐标的中位数
    sort(adjusted_x.begin(), adjusted_x.end());
    int x_median = adjusted_x[n / 2];

    // 计算总步数
    int total_steps = 0;
    for (int i = 0; i < n; i++)
    {
        total_steps += abs(x[i] - (x_median + i));
        total_steps += abs(y[i] - y_median);
    }

    cout << total_steps << endl;

    return 0;
}