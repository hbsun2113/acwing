#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char dp[(1 << 25) + 1];///储存答案
int vids[10][10];///标记是否走过该点
int n;
int maps[10][10];///地图
char m[10][10];///转换前的地图
int moves[5][2] = {{0, 0},{0, 1},{0, -1},{1, 0},{-1, 0}};///对应的位置要进行变化
void Init()///初始化函数
{
    memset(vids, 0, sizeof(vids));
    for(int i = 1; i <= 5; i ++)
        for(int j = 1; j <= 5; j ++)
            maps[i][j] = 1;///构造出全部灯都是亮的状态
    for(int i = 0; i < (1 << 25) + 1; i ++)
        dp[i] = 'a';///将答案的值全部赋值为‘a’，代表这个状态没有值
}
void change(int i, int j)///走到这个位置后，对应发生的变化
{
    for(int ii = 0; ii < 5; ii ++)
    {
        int x = i + moves[ii][0];
        int y = j + moves[ii][1];
        maps[x][y] = !maps[x][y];
    }
}
int jzchang()///将地图的状态变为二进制数
{
    int sum = ((1 << 25) - 1);///25位的1
    int num = 0;
    for(int i = 5; i != 0; i --)
    {
        for(int j = 5; j != 0; j --)
        {
            if(maps[i][j] == 0)
            {
                sum = sum ^ (1 << num);
            }
            num ++;
        }
    }
    return sum;
}
void dfs(int step)
{
    if(step == 6)
    {
        return;
    }
    for(int i = 1; i <= 5; i ++)
    {
        for(int j = 1; j <= 5; j ++)
        {
            if(vids[i][j] == 0)///如果这个位置没有被走过
            {
                vids[i][j] = 1;
            change(i, j);
            int temp = jzchang();
            if(dp[temp] == 'a')///如果当前的状态没有被走过
            {
                dp[temp] = step + 1 + '0';
                dfs(step + 1);
            }
            change(i, j);
                vids[i][j] = 0;
            }
        }
    }
}
int main()
{
    scanf("%d", &n);
    Init();
    dp[(1 << 25) - 1] = '0';///初始状态为0
    dfs(0);
    while(n --)
    {
        for(int i = 1; i <= 5; i ++)
            scanf("%s", m[i]);
        for(int i = 1; i <= 5; i ++)
        {
            for(int j = 0; j < 5; j ++)
            {
                maps[i][j + 1] = m[i][j] - '0';
            }
        }
        int t = jzchang();
        if(dp[t] == 'a')
            printf("-1\n");
        else
            printf("%d\n", dp[t] - '0');
    }
    return 0;
}

