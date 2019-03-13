#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
ll quick_pow(ll a, ll b, ll mod)
{
    ll temp = a;
    ll sum = 0;
    while(b)
    {
        if(b & 1)
        {
            sum = (sum + temp) % mod;
        }
        b >>= 1;
        temp <<= 1;
        temp %= mod;
    }
    return sum % mod;
}
ll a, b, c;
int main()
{
    while(~scanf("%lld%lld%lld", &a, &b, &c))
    {
        ll re = quick_pow(a, b, c);
        printf("%lld\n", re);
    }
    return 0;
}

