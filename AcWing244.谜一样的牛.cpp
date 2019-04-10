#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
/**
 * 5
 * 0 1 2 1 0
 * 2  4  5  3  1
 * 代表的意思是前面有几个比我小
 * 从后往前，最后一个的意思是前面都比我来得高
 * 查询第0 + 1小的数
 * 那么维护查询区间的第k大数
 * 先把所有的数插入到一个线段数里面
 * 那么查询第k大
 * **/
#define mem(x) memset(x, 0, sizeof(x))
const int MAXN = 1e5 + 5;
vector<int>vec;
struct segtree{
    int arr[MAXN];
    struct NODE{
        int l, r, sum;
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
            seg[root].sum = arr[l];
            return ;
        }
        int mid = (l + r) >> 1;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
        seg[root].sum = seg[root << 1].sum + seg[root << 1 | 1].sum;
    }
    void change(int root, int x, int y)
    {
        if(seg[root].l == x && seg[root].r == x)
        {
            seg[root].sum += y;
            return ;
        }
        int mid = (seg[root].l + seg[root].r) >> 1;
        if(x <= mid)
        {
            change(root << 1, x, y);
        }
        else if(x > mid)
        {
            change(root << 1 | 1, x, y);
        }
        seg[root].sum = seg[root << 1].sum + seg[root << 1 | 1].sum;
    }
    int query(int root, int x)
    {
        if(seg[root].l == seg[root].r)
        {
            return seg[root].l;
        }
        if(x <= seg[root << 1].sum)
        {
            return query(root << 1, x);
        }
        else if(x > seg[root << 1].sum)
        {
            return query(root << 1 | 1, x - seg[root << 1].sum);
        }
    }
}seg;
int n;
int crr[MAXN];
int main()
{
    scanf("%d", &n);
    vec.clear();
    mem(crr);
    crr[0] = 0;
    for(int i = 1; i < n; i ++)
        scanf("%d", &crr[i]);
    seg.Init();
    for(int i = 1; i <= n; i ++)
    {
        seg.arr[i] = 1;
    }
    seg.build(1, 1, n);
    for(int i = n - 1; i != -1; i --)
    {
        int num = seg.query(1, crr[i] + 1);
        vec.push_back(num);
        seg.change(1, num, -1);
    }
    for(int i = vec.size() - 1; i != -1; i --)
    {
        printf("%d\n", vec[i]);
    }
    return 0;
}

