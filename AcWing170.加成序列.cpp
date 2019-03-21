#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
/**
 x[1] = 1
 x[m] = n
 x[1] < x[2] < ...... < x[m]
 x[k] = x[i] + x[j]
 先找到dfs的状态
 假设dfs的状态为dfs(int now, int step, int last)///就是当前是第几个数，当前的层数， 上一个数的大小
 那么这个题又得玄学剪枝 + 迭代加深
 1.搜索顺序优化：那么就是采取搜索顺序优化，就采取i >= j来进行枚举，从大到小枚举
              会更快的逼近于n
 2.迭代加深：经过瞎几把分析，我们可以得知，无论是什么数，序列的长度不会超过10
           每次选择前面的arr[i]与arr[j] 假设前面无所谓，每次选择arr[i] arr[j]
           那么每次瞎搞num最优会趋近于 *2 ，那么可以得知 瞎搞的最优秀的解是大于等于 log(n) / log(2)
           反正就是log(n) / log(2) = 6.6
           但是结果肯定会大于最优秀的值6.6
           不妨使用10来试试
 3.排除等效冗余：对于不同的i和j，x[i] + x[j] 可能是相等的。我们可以用bool数组对 x[i] + x[j] 进行判重
              避免出现重复搜索同一个值
 **/
const int MAXN = 105;
int arr[MAXN];
bool vids[MAXN];
int n;
int dfs(int now, int step, int last)
{
    if(arr[now] == n)
        return now;
    if(now > step)
        return 0;
    for(int i = now; i != 0; i --)
    {
        for(int j = i; j != 0; j --)
        {
            if(!vids[arr[i] + arr[j]] && arr[i] + arr[j] >= last && arr[i] + arr[j] <= n)
            {
                vids[arr[i] + arr[j]] = 1;
                arr[now + 1] = arr[i] + arr[j];
                int flag = dfs(now + 1, step, arr[i] + arr[j]);
                if(flag != 0)
                    return flag;
                vids[arr[i] + arr[j]] = 0;
                arr[now + 1] = 0;
            }
            else if(arr[i] + arr[j] < last)
            {
                break;
            }
        }
    }
    return 0;
}
int main()
{
    while(~scanf("%d", &n) && n)
    {
        if(n == 1)
            printf("1\n");
        else
        {
        for(int i = 2; i <= 10; i ++)///设置迭代的深度
        {
            memset(arr, 0, sizeof(arr));
            memset(vids, 0, sizeof(vids));
            arr[1] = 1;
            arr[2] = 2;
            int re = dfs(2, i, arr[2]);
            if(re != 0)
            {
                for(int i = 1; i <= re; i ++)
                    printf("%d ", arr[i]);
                printf("\n");
                break;
            }
        }
        }
    }
    return 0;
}

