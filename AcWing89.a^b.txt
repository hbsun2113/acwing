#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
ll quick_pow(ll a, ll b, ll mod)
{
    ll temp = a;
    ll sum = 1;
    while(b)
    {
        if(b & 1 != 0)
        {
            sum = (sum * temp) % mod;
        }
        temp = (temp * temp) % mod;
        b >>= 1;
    }
    return sum;
}
ll a, b, c;
int main()
{
    while(~scanf("%d%d%d", &a, &b, &c))
    {
        if(b != 0)
        {
        ll re = quick_pow(a, b, c);
        printf("%lld\n", re);
        }
        else
        {
            printf("1\n");
        }
    }
    return 0;
}
