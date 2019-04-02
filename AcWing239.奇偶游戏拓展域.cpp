#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2 * 10000 + 100;
/**
扩展域并查集
就是将并查集的属性拆解成多个不同属性的并查集
那么我们可以考虑将元素的属性拆分为even域 odd域
**/
int n, m;
int pre[MAXN];
vector<int>vec;
struct node{
    int l, r, value;
} arr[MAXN];
void Init()
{
    for(int i = 0; i < MAXN; i ++)
        pre[i] = i;
    vec.clear();
    memset(arr, 0, sizeof(arr));
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
void lsh()
{
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
}
int acfinds(int x)
{
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin();
}
int main()
{
    scanf("%d%d", &n, &m);
    Init();
    char str[5];
    for(int i = 0; i < m; i ++)
    {
        scanf("%d%d%s", &arr[i].l, &arr[i].r, str);
        arr[i].value = str[0] == 'o' ?  1 : 0;
        vec.push_back(arr[i].l - 1);
        vec.push_back(arr[i].r);
    }
    lsh();
    for(int i = 0; i < m; i ++)
    {
        int a_odd = acfinds(arr[i].l - 1);
        int b_odd = acfinds(arr[i].r);
        int len = vec.size();
        int a_even = a_odd + len;
        int b_even = b_odd + len;
        if(arr[i].value == 0)
        {
            if(Get(a_odd) == Get(b_even) || Get(a_even) == Get(b_odd))
            {
                printf("%d\n", i);
                return 0;
            }
            Merge(a_odd, b_odd);
            Merge(a_even, b_even);
        }
        else
        {
            if(Get(a_odd) == Get(b_odd) || Get(a_even) == Get(b_even))
            {
                printf("%d\n", i);
                return 0;
            }
            Merge(a_odd, b_even);
            Merge(b_odd, a_even);
        }
    }
    printf("%d\n", m);
    return 0;
}
