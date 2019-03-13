#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
/**
 【思路】：枚举mid，即double mid = (l + r) / 2.0
        构造一个前缀和，sum[i] = sum[i - 1] + arr[i] - mid
        枚举i 然后枚举i - f以前的所有sum[i],如果存在sum[i] - sum[j]
        的数值 > 0 那么肯定，就可以接着向上枚举了
 
 **/
int n, f;
int arr[100000 + 5];
double sum[100000 + 5];
int maxs = 0;
bool result(double ave)
{
    memset(sum, 0, sizeof(sum));
    for(int i = 1; i <= n; i ++)
    {
        sum[i] = sum[i - 1] + double(arr[i]) - ave;
    }
    double mins = 1e9;
    for(int i = f; i <= n; i ++)
    {
        mins = min(mins, sum[i - f]);
        if(sum[i] - mins >= 0)
            return true;
    }
    return false;
}
int acfinds(int ll, int rr)
{
    double l = ll * 1.0;
    double r = rr * 1.0;
    while(r - l > 1e-5)
    {
        double mid = (l + r) / (2.0);
        if(result(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    return int(r * 1000);
}
int main()
{
    while(~scanf("%d%d", &n, &f))
    {
        maxs = 0;
        memset(arr, 0, sizeof(arr));
        memset(sum, 0, sizeof(sum));
        for(int i = 1; i <= n; i ++)
            scanf("%d", &arr[i]), maxs = max(maxs, arr[i]);
        int re = acfinds(0, maxs);
        printf("%d\n", re);
    }
    return 0;
}

