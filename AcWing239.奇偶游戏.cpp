#include <bits/stdc++.h>
using namespace std;
/**
这个题目牛逼啊
如果[l, r]代表对应的前缀和[1, l - 1] [l, r]
那么我们如果得知sum[l, r]是偶数，那么可以得知 sum[l - 1] sum[r] 的奇偶性是相同
                所以可以将sum[l - 1]与sum[r]连接
                若sum[r]为奇数，sum[l, r]为偶数，可得奇数-偶数=奇数,所以sum[l - 1]也为奇数
                若sum[r]为偶数, sum[l, r]为偶数，可得偶数-偶数=偶数,所以sum[l - 1]也为偶数
        如果得知sum[l, r]是奇数，那么可以得知 sum[l - 1] sum[r]的奇偶性是
                若sum[r]为奇数，sum[l, r]为奇数，可得奇数-奇数=偶数，所以sum[l - 1]为偶数
                若sum[r]为偶数，sum[l, r]为奇数，可得偶数-奇数=奇数，所以sum[l - 1]为奇数
那么考虑边带权，如果是相同的奇偶性，那么边权赋为1
                如果不是相同的奇偶性，那么边权赋为0
                
                
                那么考虑是否在一个并查集合内，如果在一个并查集里，那么就考虑给出的关系是否是合理的
                我们可得点到跟根节点的关系，那么点到根节点的关系是该点到root节点的所有路径的^和
                如果不在一个并查集和里面，那么考虑合并的时候的关系是什么，因为可以得到当前的点到根节点
                的关系，那么就是 合并A点的权值^合并B点的权值^还有合并的边
                
                因为数据的范围太多，所以可以先离散化
**/
typedef long long ll;
typedef struct NODE
{
    ll l, r, value;
}node;
const int MAXN = 20000 + 5;
node arr[MAXN];
vector<ll>vec;
int pre[MAXN];
int d[MAXN];///这个权值代表当前点到根节点的权值
void Init()
{
    vec.clear();
    memset(arr, 0, sizeof(arr));
    for(int i = 0; i < MAXN; i ++)
        pre[i] = i;
    memset(d, 0, sizeof(d));
}
void lsh()
{
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
}
int acfinds(ll x)
{
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin();
}
int Get(int x)
{
    if(x == pre[x])
        return x;
    else
    {
        int root = Get(pre[x]);///先查询到root, 就会从root进行更新
        ///就是等价d[x] ^= d[root]
        ///离根节点越近的，越早更新
        ///这样的话，就保证了叶子节点更新的时候，更新的是前面的所有的总和
        d[x] ^= d[pre[x]];
        return pre[x] = root;
    }
}
void Merge(int a, int b, int value)
{
    int x = Get(a);
    int y = Get(b);
    pre[x] = y;
    d[x] = (d[a] ^ d[b] ^ value);
    return ;
}
int main(){
    int n, m;
    char str[10];
    scanf("%d%d", &n, &m);
        Init();
        for(int i = 1; i <= m; i ++)
        {
            scanf("%lld%lld%s", &arr[i].l, &arr[i].r, str);
            if(str[0] == 'e')
                arr[i].value = 0;///1 - 奇 0 - 偶数
            else 
                arr[i].value = 1;
            vec.push_back(arr[i].l - 1);
            vec.push_back(arr[i].r);
        }
        lsh();
        for(int i = 1; i <= m; i ++)
        {
            int a, b;
            a = acfinds(arr[i].l - 1);
            b = acfinds(arr[i].r);
            //printf("%d %d %d\n", a, b, arr[i].value);
            if(Get(a) != Get(b))
            {
                Merge(a, b, arr[i].value);
            }
            else
            {
                int re = (d[a] ^ d[b]);
                if(re != arr[i].value)
                {
                    printf("%d\n", i - 1);
                    return 0;
                }
            }
        }
        printf("%d\n", m);
    return 0;
}
