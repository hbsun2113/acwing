#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 9901;
typedef long long ll;
/**
 等比数列求和公式：
 (- q ^ n + 1) / (1 - q)
 quick_pow
 质因数分解 + 唯一分解 + 约数求和
 
 **/
ll quick_pow(ll a, ll b)
{
    ll ans = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
        {
            ans = ans % MOD * a;
        }
        a = a % MOD * a % MOD;
        b >>= 1;
    }
    return ans;
}
ll sum(ll p, ll c)
{
    if (c == 0)
        return 1;
    if(c & 1)
        return ((1 + quick_pow(p,(c + 1) >> 1)) * sum(p,(c) >> 1)) % MOD;
    else
        return ((1 + quick_pow(p,c >> 1)) * sum(p,(c >> 1) - 1) + quick_pow(p,c)) % MOD;
}
int a, b;
int main()
{
    scanf("%d%d", &a, &b);
    ll sj = a;
    ll ans = 1;
    for(ll i = 2; i * i <= a + 1; i ++)
    {
        ll s = 0;
        while(a % i == 0)
        {
            s ++;
            a /= i;
        }
        //printf("%lld %lld\n", i, s);
        ans = ans * sum(i, s * b) % MOD;
        //printf("ans = %lld\n", ans);
    }
    if(a > 1)
        ans = ans * sum(a, b) % MOD;
    if(a == 0)
        printf("0\n");
    else
    {
        printf("%lld\n", ans);
    }
    return 0;
}


