#include <iostream>
#include <cstdio>
#include <cstring>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 5;
int n, m;
struct segtree{
    struct node{
        ll l, r, dat, sum, lazy;
    }tree[MAXN << 2];
    ll arr[MAXN];
    void Init(){
        mem(tree);
        mem(arr);
    }
    void build(int root, int l, int r){
        tree[root].l = l;
        tree[root].r = r;
        if(l == r)
        {
            tree[root].dat = arr[l];
            tree[root].sum = arr[l];
            tree[root].lazy = 0;
            return ;
        }
        int mid = (l + r) / 2;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
        tree[root].sum = tree[root << 1].sum + tree[root << 1 | 1].sum;
    }
    void push_down(int root)
    {
        if(tree[root].lazy && tree[root].l != tree[root].r)
        {
            tree[root << 1].sum += (tree[root].lazy * (tree[root << 1].r - tree[root << 1].l + 1));
            tree[root << 1 | 1].sum += (tree[root].lazy * (tree[root << 1 | 1].r - tree[root << 1 | 1].l + 1));
            tree[root << 1].lazy += tree[root].lazy;
            tree[root << 1 | 1].lazy += tree[root].lazy;
            tree[root].lazy = 0;
        }
    }
    void add(int root, int l, int r, int value)
    {
        push_down(root);
        if(tree[root].l == l && tree[root].r == r)
        {
            tree[root].lazy += value;
            tree[root].sum += ((r - l + 1) * value);
            return ;
        }
        int mid = (tree[root].l + tree[root].r) >> 1;
        if(r <= mid)
        {
            add(root << 1, l, r, value);
        }
        else if(l > mid)
        {
            add(root << 1 | 1, l, r, value);
        }
        else
        {
            add(root << 1, l, mid, value);
            add(root << 1 | 1, mid + 1, r, value);
        }
        tree[root].sum = tree[root << 1].sum + tree[root << 1 | 1].sum;
    }
    ll query(int root, int l, int r)
    {
        //printf("%d %d %d\n", root, l, r);
        push_down(root);
        if(tree[root].l == l && tree[root].r == r)
        {
            return tree[root].sum;
        }
        int mid = (tree[root].l + tree[root].r) >> 1;
        if(l > mid)
        {
            return query(root << 1 | 1, l, r);
        }
        else if(r <= mid)
        {
            return query(root << 1, l, r);
        }
        else
        {
            return query(root << 1, l, mid) + query(root << 1 | 1, mid + 1, r);
        }
    }
}seg;
int main()
{
    scanf("%d%d", &n, &m);
    seg.Init();
    for(int i = 1; i <= n; i ++)
        scanf("%lld", &seg.arr[i]);
    seg.build(1, 1, n);
    char s[2];
    for(int i = 0; i < m; i ++)
    {
        scanf("%s", s);
        if(s[0] == 'Q')
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", seg.query(1, l, r));
        }
        else
        {
            int l, r, v;
            scanf("%d%d%d", &l, &r, &v);
            seg.add(1, l, r, v);
        }
    }
    return 0;
}

