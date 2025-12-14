#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    /* 输入部分 */
    int n; scanf("%d", &n);
    
    int id[100];            // 请求编号
    int pos[100];           // 柱面号
    int visited[100] = {0}; // 标记是否处理
    for (int i = 0; i < n; i++) scanf("%d %d", &id[i], &pos[i]);
    
    int current; scanf("%d", &current);
    
    /* 逻辑处理 */
    int total_move = 0;
    int processed = 0; // 处理的请求数量

    while (processed < n) {
        /* 处理未请求结果 */
        int min_diff = INT_MAX;
        int selected_idx = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int diff = abs(pos[i] - current); // 求得距离
                
                // 距离更近的请求 或者 距离一样时柱面号更大的请求
                if (diff < min_diff ||(diff == min_diff &&
                     (selected_idx == -1 || pos[i] > pos[selected_idx]))) 
                {
                    min_diff = diff;  // 最短请求的距离
                    selected_idx = i; // 最短请求的索引
                }
            }
        }
            /* 更新状态 */
            visited[selected_idx] = 1;   // 已处理
            total_move += min_diff;      // 累计移动距离
            current = pos[selected_idx]; // 处理完的请求位置 
            processed++;                 // 处理的请求数量
        }

    printf("%d\n", total_move);
    return 0;
}
