#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
/**
 这个题目很精妙的使用了位运算
 用位运算来枚举
 0 ～ 2^16
 将输入的 4 * 4 矩阵变换成一个16位的二进制数
 如果我预先处理所有状态的答案
 再进行回答
 可以先预先处理一个按一个位置对应4 * 4矩阵变换
 的二进制数
 **/
const int MAXN = 5;
const int inf = (1 << 16);
int change[MAXN][MAXN];
void Init()
{
    memset(change, 0, sizeof(change));
}
int judge(int x, int y)///第x行 第j列
{
    int re = 0;
    for(int i = 0; i < 4; i ++)
    {
        re += (1 << (4 * x + i));
    }
    for(int i = 0; i < 4; i ++)
    {
        re += (1 << (4 * i + y));
    }
    re -= 1 << (4 * x + y);
    return re;
}
void dabiao()
{
    Init();
    for(int i = 0; i < 4; i ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            change[i][j] = judge(i, j);
        }
    }
}
char h[MAXN];
int main()
{
    dabiao();
    int num = 0;
    for(int i = 0 ; i < 4; i ++)
    {
        scanf("%s", h);
        for(int j = 0; j < 4; j ++)
        {
            if(h[j] == '+')
                num += (1 << (i * 4 + j));
        }
    }
    int mins = 0x7fffffff;
    int len = 0;
    vector<pair<int, int>>vec;
    vec.clear();
    for(int i = 0; i <= inf; i ++)
    {
        int r = num;
        len = 0;
        for(int j = 0; j < 16; j ++)
        {
            if(i >> j & 1)
            {
                r ^= change[j / 4][j % 4];
                len ++;
            }
        }
        if(len < mins && r == 0)
        {
            mins = len;
            for(int j = 0; j < 16; j ++)
            {
                if(i >> j & 1)
                    vec.push_back({j / 4 + 1, j % 4 + 1});
            }
        }
    }
    printf("%d\n", mins);
    for(int i = 0; i < vec.size(); i ++)
        printf("%d %d\n", vec[i].first, vec[i].second);
    return 0;
}

