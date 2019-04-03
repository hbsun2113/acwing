#include <bits/stdc++.h>
#define mem(a) memset(a, 0, sizeof(a))
using namespace std;
typedef long long ll;
const int MAXN = 200000 + 5;
int n;
ll arr[MAXN], crr[MAXN];
ll lowbit(ll x)///可以查找到最后面的那个1
{
    return x & -x;
}
void Init()///初始化
{
    mem(arr), mem(crr);
}
ll ask(ll x)///查询前缀和
{
    ll ans = 0;
    for(; x; x -= (x & -x))
        ans += crr[x];
    return ans;
}
void add(ll x, ll y)///单点修改
{
    for(; x <= n; x += (x & -x))
    {
        crr[x] += y;
    }
}
/**
一开始所有的arr里都是0
这个代表的是值为value的点出现的次数，出现一次就add(value, 1)
第一个情况即 V 那么从后往前插入，每次插入就查询比这个数值来得大的值
即ask(max_value) - ask(arr[i])就可以得到当前的点后面比他大的数有多少
从前往后插，一样的道理，也可以得到对应的点前面比他大的数有多少
**/
ll l1[MAXN], r1[MAXN];
int main()
{
    scanf("%d", &n);
    Init();
    ll maxs = -1;
    for(int i = 0; i < n; i ++)
    {
        scanf("%lld", &arr[i]);
        maxs = max(maxs, arr[i]);
    }
    for(int i = n - 1; i != -1; i --)
    {
        add(arr[i], 1);
        r1[i] = ask(maxs) - ask(arr[i]);
    }
    mem(crr);
    for(int i = 0; i < n; i ++)
    {
        add(arr[i], 1);
        l1[i] = ask(maxs) - ask(arr[i]);
    }
    ll re1 = 0;
    for(int i = 0; i < n; i ++)
        re1 += (l1[i] * r1[i]);
    mem(crr), mem(l1), mem(r1);
    for(int i = 0; i < n; i ++)
    {
        add(arr[i], 1);
        l1[i] = ask(arr[i] - 1);
    }
    mem(crr);
    for(int i = n - 1; i != -1; i --)
    {
        add(arr[i], 1);
        r1[i] = ask(arr[i] - 1);
    }
    ll re2 = 0;
    for(int i = 0; i < n; i ++)
    {
        re2 += (l1[i] * r1[i]);
    }
    printf("%lld %lld\n", re1, re2);
    return 0;
}
