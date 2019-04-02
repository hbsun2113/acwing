#include <bits/stdc++.h>
using namespace std;
/**
食物链本题以前写过边带权
所以写一下拓展域，拓展域真香
存在三个域
同类域 捕食域 天敌域
similar predation enemy

那么假设是同类
那么similar predation enemy 相互连接
假设x 吃 y
Merge x.predation y.similar
Merge x.enemy y.predation
Merge y.enemy x.similar

如果说是同类的话，那么连接的时候先判断Get(x.enemy) == Get(y.similar) || Get(x.predation) == Get(y.similar)
                                       || Get(y.enemy) == Get(x.similar) || Get(y.enemy) == Get(x.similar)
如果说是捕食的话，那么连接的时候先判断Get(x.similar) == Get(y.similar) || Get(x.enemy) == Get(y.similar)
                                       || Get(y.predation) == Get(x.similar)
**/
const int MAXN = 50000 * 3 + 100;
int pre[MAXN];
void Init()
{
    for(int i = 0; i < MAXN; i ++)
        pre[i] = i;
}
int Get(int x)
{
    return x == pre[x] ? x : pre[x] = Get(pre[x]);
}
void Merge(int x, int y)
{
    int a = Get(x);
    int b = Get(y);
    if(a != b)
        pre[a] = b;
}
int n, k;
int main()
{
    scanf("%d%d", &n, &k);
    Init();
    int wa = 0;
    for(int i = 0; i < k; i ++)
    {
        int d, x, y;
        scanf("%d%d%d", &d, &x, &y);
        if(x > n || y > n)
        {
            wa ++;
            continue;
        }
        if(x == y && d == 2)
        {
            wa ++;
            continue;
        }
        int x_sim = x;
        int y_sim = y;
        int x_pre = x + n;
        int y_pre = y + n;
        int x_ene = x + 2 * n;
        int y_ene = y + 2 * n;
        if(d == 1)
        {
            if(Get(x_pre) == Get(y_sim) || Get(x_ene) == Get(y_sim) || Get(y_pre) == Get(x_sim) || Get(y_ene) == Get(x_sim))
            {
                wa ++;
                continue;
            }
            Merge(x_sim, y_sim);
            Merge(x_pre, y_pre);
            Merge(x_ene, y_ene);
        }
        else if(d == 2)
        {
            if(Get(x_sim) == Get(y_sim) || Get(x_ene) == Get(y_sim) || Get(y_pre) == Get(x_sim))
            {
                wa ++;
                continue;
            }
            Merge(x_pre, y_sim);
            Merge(x_sim, y_ene);
            Merge(x_ene, y_pre);
        }
    }
    printf("%d\n", wa);
    return 0;
}
