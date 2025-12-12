#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N1, N2;
    cin >> N1;
    vector<int> A(N1);
    for (int i = 0; i < N1; i++)
        cin >> A[i];

    cin >> N2;
    vector<int> B(N2);
    for (int i = 0; i < N2; i++)
        cin >> B[i];

    int total = N1 + N2;
    int midIndex = (total - 1) / 2; // 低位中位数下标

    int i = 0, j = 0, count = 0, ans = 0;

    while (i < N1 || j < N2)
    {
        int val;
        if (i < N1 && (j >= N2 || A[i] <= B[j]))//必须选a的条件。a还有，b没了，a比b小
        {
            val = A[i++];
        }
        else
        {
            val = B[j++];
        }
        if (count == midIndex)
        {
            ans = val;
            break;
        }
        count++;
    }

    cout << ans << '\n';
    return 0;
}
