#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;
/**
 首先我们先发现这个题目的数组给出的数字是有序的
 那么我们可以先压缩成对应的二元组，即对应的<a, b>
 代表数值为a出现了b次
 那么我们只要确定了[l, r]中的最大出现值即可，那么就是求区间的最大值
 那么就是对应的RMQ问题（ST表）
 但是要考虑[l, r]对应的数组可能不是完整的数组
 left[i] 的含义是当前i对应的l是多少
 right[i] 的含义是当前i对应的r是多少
 num[i] 代表当前i是第几段
 val[i] 代表第i段的最大值是多少
 dp[i][j] 代表第i - i + 2 ^ (j - 1) - 1段的最大值
 if(num[l] + 1 <= num[r] - 1)
 RMQ(num[l] + 1, num[r] - 1)
 
    min(right[l], r) - l + 1
    r - max(left[l], l) + 1
 **/
const int MAXN = 100000 + 5;
const int M = 30;
int arr[MAXN], lefts[MAXN], rights[MAXN], num[MAXN], value[MAXN];
int f[MAXN][M];
void Init()
{
    mem(arr), mem(lefts), mem(rights), mem(num), mem(f), mem(value);
}
int n, m;
struct NODE
{
    int l, r, value;
};
vector<NODE>vec;
void ST_prework(int len)
{
    for(int i = 1; i <= len; i ++)
        f[i][0] = value[i];
    int t = log(len) / log(2) + 1;
    for(int j = 1; j < t; j ++)
    {
        for(int i = 1; i <= n - (1 << j) + 1; i ++)
        {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int ST_query(int l, int r)
{
    int k = log(r - l + 1) / log(2);
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}
int main()
{
    while(~scanf("%d", &n) && n)
    {
        scanf("%d", &m);
        Init();
        vec.clear();
        for(int i = 1; i <= n; i ++)
        {
            scanf("%d", &arr[i]);
        }
        NODE a;
        int temp = arr[1];
        a.l = 1;
        a.r = a.l;
        a.value = 1;
        for(int i = 2; i <= n; i ++)
        {
            if(arr[i] != temp)
            {
                temp = arr[i];
                vec.push_back(a);
                a.l = i;
                a.r = a.l;
                a.value = 1;
            }
            else
            {
                a.r = i;
                a.value ++;
            }
        }
        vec.push_back(a);
        for(int i = 0; i < vec.size(); i ++)
        {
            value[i + 1] = vec[i].value;
            for(int j = vec[i].l; j <= vec[i].r; j ++)
            {
                lefts[j] = vec[i].l;
                rights[j] = vec[i].r;
                num[j] = i + 1;
            }
        }
        ST_prework(vec.size());
        for(int i = 0; i < m; i ++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            int re;
            re = max(min(rights[l], r) - l + 1, r - max(lefts[r], l) + 1);
            if(num[l] + 1 <= num[r] - 1)
            {
                re = max(re, ST_query(num[l] + 1, num[r] - 1));
            }
            printf("%d\n", re);
        }
    }
}

