#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int N = 1e5 + 9;

int visit[N];

int procress, total;

int main() {
    /* input */
    int n;
    cin >> n;
    int id[N], val[N];
    for (int i = 1; i <= n; i++)
    cin >> id[i] >> val[i];
    int cur;
    cin >> cur;
    /* 优先距离越小 距离相同时优先下标越小*/
    while (procress < n) {
        int min = 1e9 + 1;
        int index = -1;
        for (int i = 1; i <= n; i++) {
            if (!visit[i]) {
                int diff = abs(cur - val[i]);
                if (diff < min || 
                (diff == min && (index == -1 || val[i] > val[index]))) {
                    min = diff;
                    index = i;
                }
            }
        }
        /* 标记 累加 变位置 改变请求数量*/
        visit[index] = 1;
        total += min;
        cur = val[index];
        procress ++;
    }
    cout << total;
    return 0;
}