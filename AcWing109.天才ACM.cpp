#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define mem(a) memset(a, 0, sizeof(a))
using namespace std;
/**
 思路：如果采取sort进行排序，不进行归并就会tle
 归并遇到的最大的问题是，[l, l + p] [l + p, r]
 因为l + p会重叠，所以我的写法是每次倍增后进行
 判断的区间为[l, l + p)
 所以可以避免重叠区间，但是重叠区间的写法，会对
 最后的结果进行影响，那么考虑最后为[n, n + 1)的
 情况，因为while(l < n)所以等于n的情况，应该是的
 一段，那么我们只要判断judge() == true 的情况下
 那么l == n把答案加1
 即可accept
 **/
const int MAXN = 500000 * 2 + 5;
typedef long long ll;
ll arr[MAXN];///初始数组
ll brr[MAXN];///中转数组
ll crr[MAXN];///归并答案存储的数组
ll k, n, m, t;
inline void merge(int l, int mid, int r)///归并分为两段区间[l, mid)  [mid, r]
{
    int num = l;
    int i, j;
    i = l, j = mid;
    while(i < mid && j <= r)
    {
        if(brr[i] < brr[j])
        {
            crr[num ++] = brr[i];
            i ++;
        }
        else
        {
            crr[num ++] = brr[j];
            j ++;
        }
    }
    while(i < mid)
    {
        crr[num ++] = brr[i];
        i ++;
    }
    while(j <= r)
    {
        crr[num ++] = brr[j];
        j ++;
    }
}
bool judge(int l, int r, int begins)///处理的为[l, r)左闭右开区间
{
    for(int i = l; i < r; i ++)
        brr[i] = arr[i];
    sort(brr + l, brr + r);///对左闭右开区间进行排序
    merge(begins, l, r - 1);///对前面的[begin, l) [l, r)进行归并
    int len = r - begins;///因为左闭右开,所以区间长度为r - begin
    ll sum = 0;
    int step = 0;
    for(int i = begins; i < begins + len / 2; i ++)
    {
        step ++;
        sum = sum + (crr[i] - crr[r - i - 1 + begins]) * (crr[i] - crr[r - i - 1 + begins]);
        if(step == m || sum > t)
        {
            break;
        }
    }
    if(sum > t)
        return false;
    else
        return true;
}
int main()
{
    scanf("%lld", &k);
    while(k --)
    {
        scanf("%lld%lld%lld", &n, &m, &t);
        for(int i = 0; i < n; i ++)
            scanf("%lld", &arr[i]);
        int l, rel, p, ll;
        ll = l = 0;
        p = 1;
        rel = l;
        int re = 0;
        while(l < n)
        {
            if(l + p <= n && judge(l, l + p, rel))///[l, l + p)为新增的区间
            {
                l = l + p;
                if(l == n)///因为[l, l + p)的区间，所以会存在边界l == n的情况为最后一个符合的条件，所以加上特判
                    re ++;
                for(int i = rel; i < l; i ++)
                {
                    brr[i] = crr[i];
                }
                p *= 2;
            }
            else
            {
                p /= 2;
                if(p == 0)///不到达最后的状态，并且不可倍增
                {
                    re ++;
                    p = 1;
                    rel = l;
                }
            }
        }
        printf("%d\n", re);
    }
    return 0;
}
