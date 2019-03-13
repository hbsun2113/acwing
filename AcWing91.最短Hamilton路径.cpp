#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int maps[25][25];
int dp[(1 << 20) + 5][25];
int n;
int main()
{
    scanf("%d", &n);
    memset(maps, 0, sizeof(maps));
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            scanf("%d", &maps[i][j]);
    dp[1][0] = 0;
    for(int i = 1; i < (1 << n); i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            if((i >> j & 1))
            {
                for(int k = 0; k < n; k ++)
                {
                    if((i ^ (1 << j)) >> k & 1)
                    {
                        dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][k] + maps[k][j]);
                    }
                }
            }
        }
    }
    printf("%d\n", dp[(1 << n) - 1][n - 1]);
    return 0;
}

