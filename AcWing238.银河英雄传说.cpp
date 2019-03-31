#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 30000 + 15;
/**
其实这个题目的思路就是一个边带权的想法
emmmmm，我想那么久干什么哦，就是用边权
的传递来维护答案，前面想错了，瞎写
**/
int pre[MAXN];
int dist[MAXN];
int size[MAXN];///代表每个集合的大小
void Init()
{
    for(int i = 0; i < MAXN; i ++){
        pre[i] = i;
        size[i] = 1;
    }
    memset(dist, 0, sizeof(dist));
}
int Get(int x)
{
    if(x == pre[x]){
        return x;
    }
    int root = Get(pre[x]);
    dist[x] += dist[pre[x]];///dist的距离为当前的dist[x] + dist[pre[x]]为dist的值加上父节点的值
    return pre[x] = root;
}
void Merge(int x, int y)
{
    int a = Get(x);///查询x的父节点
    int b = Get(y);///查询y的父节点
    pre[a] = b;
    dist[a] = size[b];///本来的a是没有权值的，然后a加到b的后面就可以得到dist[a]的值为size[b]
    size[b] += size[a];///那么size[b]的个数得到增加为size[b] + size[a]
}
int n;
int main()
{
    scanf("%d", &n);
    Init();
    for(int i = 0; i < n; i ++)
    {
        char tp;
        int a, b;
        getchar();
        scanf("%c%d%d", &tp, &a, &b);
        if(tp == 'M')
        {
            Merge(a, b);
        }
        else
        {
            if(Get(a) == Get(b))
            {
                printf("%d\n", abs(dist[a] - dist[b]) - 1);
            }
            else
            {
                printf("-1\n");
            }
        }
    }
    return 0;
}
