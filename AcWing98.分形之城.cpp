#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
ll n, a, b, c;
/**
以(0,0)为原点进行旋转
 那么普及顺时针旋转公式
 （x，y）【cos x  sin x】
        【- sinx cos x】
 那么len为当前的单位长度
 cnt 为城市的个数
 **/
pll calc(ll n, ll m)
{
    if(n == 0)
        return {0, 0};
    ll len = 1ll << (n - 1);///边长
    ll cnt = 1ll << 2 * (n - 1);///城市的个数
    pll pos = calc(n - 1, m % cnt);
    ll cases = m / cnt;
    if(cases == 0) return {pos.second, pos.first};
    else if(cases == 1) return {pos.first, pos.second + len};
    else if(cases == 2) return {pos.first + len, pos.second + len};
    else return {- pos.second + 2 * len - 1, - pos.first + len - 1};
}
int main()
{
    while(~scanf("%lld", &n))
    {
        for(int i = 0; i < n; i ++)
        {
            scanf("%lld %lld %lld", &a, &b, &c);
            pll x = calc(a, b - 1);
            pll y = calc(a, c - 1);
            double x1 = x.first - y.first;
            double y1 = x.second - y.second;
            double re = sqrt(x1 * x1 + y1 * y1) * 10.0;
            printf("%.0lf\n", re);
        }
    }
    return 0;
}





