#include <bits/stdc++.h>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;
typedef long long ll;
const int MAXN = 100000 + 5;
ll arr[MAXN];
struct node
{
    int l, r, lazy;
    ll dat;
}seg[MAXN << 2];
void Init()
{
    mem(arr);
    mem(seg);
}
void build(int root, int l, int r)
{
    seg[root].l = l;
    seg[root].r = r;
    if(l == r)
    {
        seg[root].dat = arr[l];
        seg[root].lazy = 0;
        return ;
    }
    int mid = (l + r) >> 1;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid + 1, r);
    seg[root].lazy = 0;
    seg[root].dat = 0;
    return ;
}
void change(int root, int l, int r, int value)
{
    if(seg[root].l == l && seg[root].r == r)
    {
        seg[root].lazy += value;
        return ;
    }
    int mid = (seg[root].l + seg[root].r) >> 1;
    if(r <= mid)
    {
        change(root << 1, l, r, value);
    }
    else if(l > mid)
    {
        change(root << 1 | 1, l, r, value);
    }
    else
    {
        change(root << 1, l, mid, value);
        change(root << 1 | 1, mid + 1, r, value);
    }
}
void push_down(int root)
{
    if(seg[root].lazy)
    {
        seg[root].dat += seg[root].lazy;
        if(seg[root].l != seg[root].r)
        {
        seg[root << 1].lazy += seg[root].lazy;
        seg[root << 1 | 1].lazy += seg[root].lazy;
        }
        seg[root].lazy = 0;
    }
}
ll ask(int root, int x)
{
    push_down(root);
    if(seg[root].l == x && seg[root].r == x)
    {
        return seg[root].dat;
    }
    int mid = (seg[root].l + seg[root].r) >> 1;
    if(x <= mid)
    {
        return ask(root << 1, x);
    }
    else
    {
        return ask(root << 1 | 1, x);
    }
}
int n, m;
int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        Init();
        for(int i = 1; i <= n; i ++)
        {
            scanf("%lld", &arr[i]);
        }
        char s[2];
        build(1, 1, n);
        for(int i = 0; i < m; i ++)
        {
            scanf("%s", s);
            if(s[0] == 'Q')
            {
                int num;
                scanf("%d", &num);
                ll re = ask(1, num);
                printf("%lld\n", re);
            }
            else
            {
                int l, r, d;
                scanf("%d%d%d", &l, &r, &d);
                change(1, l, r, d);
            }
        }
    }
    return 0;
}
