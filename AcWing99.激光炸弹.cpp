#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
/**
 一维前缀和：sum[i] = sum[i - 1] + arr[i]
 那么我们讨论下二维的前缀和
 sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j]
 含义是少一行的前缀和 + 少一列的前缀和 因为这两个相加会有重复的区间 即sum[i - 1][j - 1]
 那么减去一个sum[i - 1][j - 1],只有arr[i][j]没有加入，那么加入arr[i][j]即更新完二维
 的前缀和
 
 接下来是空间为r的正方形的枚举，那么sum[i][j] - sum[i - r][j] - sum[i][j - r] + sum[i - r][j - r]
 这样就成功枚举了长度为r的正方形
 **/
const int MAXN = 5000 + 5;
int sum[MAXN][MAXN];
void Init()
{
    memset(sum, 0, sizeof(sum));
}
int n, r, x_max, y_max;
int main()
{
    scanf("%d%d", &n, &r);
    x_max = y_max = r;
    Init();
    for(int i = 0; i < n; i ++)
    {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        x ++;
        y ++;
        sum[x][y] += w;
        x_max = max(x_max, x);
        y_max = max(y_max, y);
    }
    for(int i = 1; i <= x_max; i ++)
    {
        for(int j = 1; j <= y_max; j ++)
        {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + sum[i][j];
        }
    }
    int re = 0;
    for(int i = r; i <= x_max; i ++)
    {
        for(int j = r; j <= y_max; j ++)
        {
            re = max(re, sum[i][j] - sum[i][j - r] - sum[i - r][j] + sum[i - r][j - r]);
        }
    }
    printf("%d", re);
    return 0;
}

