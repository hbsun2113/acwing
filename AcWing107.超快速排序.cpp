#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/**
 逆序对的定义：
 对于一个序列a，若 i < j 且 a[i] > a[j], 则称a[i] 与 a[j]构成逆序对
 先科普下归并排序求逆序对
 归并排序可以在O(nlogn)的时间复杂度
 里面求出数组的逆序对
 归并排序是每次把序列进行二分
 递归左右两半排序，然后合并两个有序序列
 那么在进行归并排序的时候考虑
 把左右两边各自内部的逆序对数作为子问题来求解
 就是双指针
 懂了
 **/
const int MAXN = 500000 + 5;
typedef long long ll;
ll arr[MAXN];
ll brr[MAXN];
int n;
ll re = 0;
void merge(int l, int r)
{
    int mid = (l + r) / 2;
    int i = l, j = mid + 1;
    if(r - l < 1)
        return ;
    merge(l, mid);
    merge(mid + 1, r);
    for(int k = l; k <= r; k ++)
    {
        /**
            双指针的思想
         **/
        if(j > r || (i <= mid && arr[i] < arr[j]))
        {
            brr[k] = arr[i ++];
        }
        else
        {
            brr[k] = arr[j ++];
            re += (mid - i + 1);
        }
    }
    for(int k = l; k <= r; k ++)
        arr[k] = brr[k];
}
int main()
{
    while(~scanf("%d", &n) && n)
    {
        re = 0;
        for(int i = 1; i <= n; i ++)
            scanf("%d", &arr[i]);
        merge(1, n);
        printf("%lld\n", re);
    }
    return 0;
}

