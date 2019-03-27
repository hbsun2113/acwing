#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define mem(x) memset(x, 0, sizeof(x))
/**
 那么我的考虑是使用一个vec来进行操作
 那么问题又来了，我们要怎么维护呢？
 sort一下每个牛的开始时间，结束时间
 那么我们来排序按照开始的时间升序排序
 然后按照结束的时间降序排序
 TLE了，这里有个更好的想法，因为每次只要保存最后一个
 没必要用一个vec数组，用一个vec就okk了
 找最靠近更新的值的那个
 就可以了
 这样贪心应该是对的吧
 gg了，二分是不对的，因为在二分的过程中，涉及了修改
 那么就不是有序的，那么就是错误的，哭了
 所以这个题目只能使用优先队列来处理这个题目
 **/
typedef struct COW
{
    int num, l, r;
    bool friend operator < (const COW &a, const COW &b)
    {
        if(a.r != b.r)
        {
            return a.r > b.r;///从小到大排序
        }
        else
        {
            return a.l > b.l;///从小到大排序
        }
    }
}cow;
const int MAXN = 50000 + 5;
cow arr[MAXN];
int re[MAXN];
bool cmp(const cow &a, const cow &b)
{
    if(a.l != b.l)
        return a.l < b.l;
    else
        return a.r < b.r;
}
int n;
priority_queue<cow>que;
void Init()
{
    while(!que.empty())
        que.pop();
    mem(arr);
    mem(re);
}
int main()
{
    while(~scanf("%d", &n))
    {
        Init();
        for(int i = 0; i < n; i ++)
        {
            scanf("%d%d", &arr[i].l, &arr[i].r);
            arr[i].num = i;
        }
        sort(arr, arr + n, cmp);
        int len = 0;
        for(int i = 0; i < n; i ++)
        {
            if(que.empty() || que.top().r >= arr[i].l)
            {
                re[arr[i].num] = ++len;
                que.push(arr[i]);
            }
            else
            {
                re[arr[i].num] = re[que.top().num];
                que.pop();
                que.push(arr[i]);
            }
        }
        printf("%d\n", len);
        for(int i = 0; i < n; i ++)
        {
            printf("%d\n", re[i]);
        }
    }
    return 0;
}

