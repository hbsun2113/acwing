#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
/**
 【思路】：通过给出的数列，构造出差分数列，即差分数列b
 b[0] = a[0]
 for(int i = 1; i < n; i ++)
    b[i] = a[i] - a[i - 1]
 就得到了差分最后求和的数列
 我们的目标是构成除b[0]
 b[i ~ n] = 0
 哦哦哦哦哦
 我懂了，因为我们得到了差分序列
 那么让差分序列2 - n为0即可
 那么我们可以在l r的位置+1或者-1
 这样是一个[l,r]的更新，只要差分数列为0
 那么就是一样的
 我们只要正负配对即可
 **/
int n;
long long p, q;
const int MAXN = 1e5 + 5;
long long arr[MAXN];
long long sum[MAXN];
int main()
{
    scanf("%d", &n);
    p = q = 0;
    for(int i = 0; i < n; i ++)
    {
        scanf("%lld", &arr[i]);
    }
    sum[0] = arr[0];
    for(int i = 1; i < n; i ++)
        sum[i] = arr[i] - arr[i - 1];
    for(int i = 1; i < n; i ++)
    {
        if(sum[i] > 0)
            p += sum[i];
        else
            q -= sum[i];
    }
    printf("%lld\n%lld\n", max(p, q), abs(p - q) + 1);
    return 0;
}
/**
DSC ORZ
**/
