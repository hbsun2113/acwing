#include <iostream>
#include <cstdio>
/***
 【题意】：
    2 3
    3 2
 （2， 3）== （3， 2）
 搜索前面的状态或者搜索后面的状态
 只搜索其中之一
 
 
    尚未裁截前的状态是为n个等长的木棒
    题目说把这n个等长的木棒瞎搞了，变成m根小木棒
    题目要求将m根小木棒复原为n根等长的木棒，并且是最小长度的
 
    枚举原始木棒 最小长度
    max(arr[1 - m]) - sum(arr[1 -n])
    最优情况下，是没有砍断的
    最差情况下，是只能构成一根

    判断枚举的长度是否合法？
 
    dfs(int step, int cab)
    step为正在拼凑的棒数
    cab为当前拼凑出来的长度
 
    搜索的第一步先选择一根木棒，
    cab为当前拼凑的木棒的长度，0
    (1)cab + arr[i] < len
        dfs(step, cab + arr[i])
    (2)cab + arr[i] == len
        dfs(step + 1, 0)
    if(step == sum / len + 1)
            return true;
    (3)cab + arr[i] > len
            continue
 
    假设我们选择第i根木棍，i - n
    从大到小排序，我选择cab + arr[i] 最大的并且 小于或等于len
    如果我选择了第i根，那么i前面不可能在下一步被选择了
    6 5 4 3 2 1
    3还没到达len
    6 5 4
    6 or 5 or 4
    3 - 1
    max - sum
    不能拼凑出len 2   > 10
 return false;
 
9
 5 2 1 5 2 1 5 2 1
 
 
 5 2 5 2 1 1 2 1 5
 
 5 1 5 1 5 1 2 2 2
 
 len : 5 ～ sum(arr[i])
 if(sum % len == 0)
    一开始的状态有可能是sum / len根 len长度的木棒
    看能否构成sum / len根的长度为len的木棒
 
 dfs(step, cab)
 step 为我们当前拼好的棒数
 cab 为我们当前拼凑出的长度
 
 cab > len 不合法
 cab == len dfs(step + 1, 0)
 cab < len 未选择的木棒里面选出一根木棒 dfs(step, cab + arr[i]) /// 我们接下来选择的木棒的长度
 
 4 dfs(step + 1, 0)
 if : step == sum / len + 1
 return
 ***/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define mem(a) memset(a, 0, sizeof(a))
using namespace std;
const int MAXN = 105;
int arr[MAXN];
int vids[MAXN];
int n, maxs, sum, len, cnt;
bool cmp(const int &a, const int &b)
{
    return a > b;
}
bool dfs(int step, int cab, int last)///last代表下一步从哪开始选择
{
    if(step > cnt)///出口
    {
        return true;///当前我们枚举的len长度是合法
    }
    if(cab == len)///拼好一根的情况下
    {
        return dfs(step + 1, 0, 0);
    }
    int fail = 0;
    for(int i = last; i < n; i ++)
    {
        if(!vids[i] && cab + arr[i] <= len && arr[i] != fail)///前面条件都不满足，那么从n根木棒里选择
        {
            vids[i] = 1;///选过当前木棒
            if(dfs(step, cab + arr[i], i + 1))///true false
                return true;///当前的方案是可行的
            fail = arr[i];
            vids[i] = 0;///回溯状态
            if(cab == 0 || cab + arr[i] == len)///剪枝(3),(4)
                return false;
        }
    }
    return false;
}
int main()
{
    while(~scanf("%d", &n) && n)
    {
        maxs = sum = 0;
        int true_n = 0;
        for(int i = 0; i < n; i ++)
        {
            int x;
            scanf("%d", &x);
            if(x > 50)///这个题目的数据会有大于50的
                continue;
            arr[true_n] = x;
            maxs = max(maxs, arr[true_n]);
            sum += arr[true_n];
            true_n ++;
        }
        n = true_n;
        sort(arr, arr + n, cmp);///从大到小排序，就可以去掉x->y,y->x的情况，从大到小的情况
        for(int i = maxs; i <= sum; i ++)///枚举长度
        {
            len = i;
            cnt = sum / len;
            mem(vids);///memset(vids, 0, sizeof(vids));
            if(sum % len == 0)///能被整除的状态
            {
                if(dfs(1, 0, 0))
                {
                    printf("%d\n", len);
                    break;
                }
            }
        }
    }
    return 0;
}


