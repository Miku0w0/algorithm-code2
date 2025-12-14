#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    vector<int> unknown;        // 未知位置下标
    vector<int> used(n + 1, 0); // 标记已用数字

    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
        if (A[i] == 0)
            unknown.push_back(i);
        else
            used[A[i]] = 1;
    }

    vector<int> nums;
    for (int i = 1; i <= n; i++)
        if (!used[i])
            nums.push_back(i);

    int ans = 0;
    sort(nums.begin(), nums.end());
    do
    {
        // 填入未知位置
        for (int i = 0; i < unknown.size(); i++)
            A[unknown[i]] = nums[i];

        // 统计顺序对
        int count = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (A[i] < A[j])
                    count++;

        if (count == k)
            ans++;
    } while (next_permutation(nums.begin(), nums.end()));

    cout << ans << "\n";
    return 0;
}
