#include <bits/stdc++.h>
#define mem(a) memset(a, 0, sizeof(a))
using namespace std;
/**
数状数组的妙用，妙啊
使用一个前缀brr数组来差分
标记区间，那么使用树状数组来维护brr数组
那么每次查询只要输出arr[i] + ask(x)
这样的话就可以实现树状数组区间更新单点查询
**/
typedef long long ll;
const int MAXN = 1e5 + 5;
ll arr[MAXN];
ll brr[MAXN];
int n, m;
void add(int x, int y)
{
    for(; x <= n; x += (x & -x))
    {
        brr[x] += y;
    }
}
ll ask(int x)
{
    ll ans = 0;
    for(; x; x -= (x & -x))
    {
        ans += brr[x];
    }
    return ans;
}
void Init()
{
    mem(arr), mem(brr);
}
int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        Init();
        for(int i = 1; i <= n; i ++)
        {
            scanf("%lld", &arr[i]);
        }
        char s[2];
        for(int i = 0; i < m; i ++)
        {
            scanf("%s", s);
            if(s[0] == 'Q')
            {
                int a;
                scanf("%d", &a);
                printf("%lld\n", ask(a) + arr[a]);
            }
            else 
            {
                int l, r, value;
                scanf("%d%d%d", &l, &r, &value);
                add(l, value);
                add(r + 1, -value);
            }
        }
    }
    return 0;
}
