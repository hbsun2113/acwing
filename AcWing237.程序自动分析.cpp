#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
/**
 并查集瞎搞系列
 = 的连接在同一个父节点下
 != 的话,判断是否在一个父节点下
 如果是的话，那就是NO
 
 但是如果先给出不等于
 那么咋整啊？
 
 改个顺序，对答案没有影响吧
 
 那么不用sort，输入的时候分两堆
 
 1的放一堆，0的放一堆
 
 先用1的建并查集，然后0再去判断
 **/
const int MAXN = 1000000 + 5;
typedef struct NODE
{
    int i, j, e;
}node;
typedef long long ll;
vector<node>vec1;
vector<node>vec2;
vector<ll>vec;
int pre[MAXN];
void Init()
{
    vec.clear();
    vec1.clear();
    vec2.clear();
    for(int i = 0; i < MAXN; i ++)
    {
        pre[i] = i;
    }
}
bool cmp(const ll & a, const ll &b)
{
    return a < b;
}
void lsh()
{
    sort(vec.begin(), vec.end(), cmp);
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
}
int finds(int x)
{
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1;
}
int acfinds(int x)
{
    return pre[x] == x ? x : pre[x] = acfinds(pre[x]);
}
bool same(int a, int b)
{
    int x = acfinds(a);
    int y = acfinds(b);
    if(x == y)
        return true;
    else
        return false;
}
void join(int a, int b)
{
    int x = acfinds(a);
    int y = acfinds(b);
    pre[x] = y;
}
int t;
int main()
{
    scanf("%d", &t);
    while(t --)
    {
        int n;
        scanf("%d", &n);
        Init();
        for(int i = 0; i < n; i ++)
        {
            node a;
            scanf("%d%d%d", &a.i, &a.j, &a.e);
            if(a.e == 1)
            {
                vec1.push_back(a);
            }
            else
            {
                vec2.push_back(a);
            }
            vec.push_back(a.i);
            vec.push_back(a.j);
        }
        lsh();
        for(int i = 0; i < vec1.size(); i ++)
        {
            join(finds(vec1[i].i), finds(vec1[i].j));
        }
        bool flag = true;
        for(int i = 0; i < vec2.size(); i ++)
        {
            if(same(finds(vec2[i].i), finds(vec2[i].j)))
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}

