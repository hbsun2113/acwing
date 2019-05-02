#include <bits/stdc++.h>
using namespace std;
#define mem(x) memset(x, 0, sizeof(x))
const int MAXN = 500000 << 2;
struct NODE{
    int l, r, sum, lsum, rsum, dat;
};
struct Segtree{
    int arr[MAXN >> 1];
    NODE tree[MAXN];
    void push_up(int root){
        tree[root].sum = tree[root << 1 | 1].sum + tree[root << 1].sum;
        tree[root].lsum = max(tree[root << 1].lsum, tree[root << 1].sum + tree[root << 1 | 1].lsum);
        tree[root].rsum = max(tree[root << 1 | 1].rsum, tree[root << 1 | 1].sum + tree[root << 1].rsum);
        tree[root].dat = max(max(tree[root << 1].dat, tree[root << 1 | 1].dat), tree[root << 1].rsum + tree[root << 1 | 1].lsum);
        return ;
    }
    void build(int root, int l, int r){
        tree[root].l = l;
        tree[root].r = r;
        if(l == r){
            tree[root].lsum = tree[root].rsum = tree[root].dat = tree[root].sum = arr[l];
            return ;
        }
        int mid = (l + r) >> 1;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
        push_up(root);
    }
    void change(int root, int l, int r, int value){
        if(tree[root].l == l && tree[root].r == r){
            tree[root].lsum = tree[root].rsum = tree[root].dat = tree[root].sum = value;
            return ;
        }
        int mid = (tree[root].l + tree[root].r) >> 1;
        if(l <= mid){
            change(root << 1, l, r, value);
        }
        else{
            change(root << 1 | 1, l, r, value);
        }
        push_up(root);
    }
    NODE query(int root, int l, int r){
        if(tree[root].l == l && tree[root].r == r){
            return tree[root];
        }
        int mid = (tree[root].l + tree[root].r) >> 1;
        /**
         * 思考一下：如果返回的点是node，那么我应该做的是
         * 一层一层向上返回对应的点，那么更新到最后，返回的点
         * 就是我要的答案。
         * **/
        int val = -(1 << 30);///这里如果是0x7fffffff，那么答案就会从负数爆到正数
        NODE father, lson, rson;///三个点对应father，lson，rson
        lson.sum = lson.lsum = lson.rsum = lson.dat = val;
        rson.sum = rson.lsum = rson.rsum = rson.dat = val;
        father.sum = 0;
        /**
         * 对于下面的理解：我是这样想的，假设我们查询到底，那么底肯定在我们查询的区间里
         * 那么我们就可以更新当前的点的sum,lsum,rsum,dat;这样的更新肯定是可以的
         * 那么当我们从一层出来的时候，得到的是对应的区间的值，那么往上更新就可以了
         * 跟题解的代码是相似
         * **/
        if(l > mid){
            rson = query(root << 1 | 1, l, r);
            father.sum += rson.sum;
        }
        else if(r <= mid){
            lson = query(root << 1, l, r);
            father.sum += lson.sum;
        }
        else{
            lson = query(root << 1, l, mid);
            rson = query(root << 1 | 1, mid + 1, r);
            father.sum = father.sum + lson.sum + rson.sum;
        }
        father.lsum = max(lson.lsum, lson.sum + rson.lsum);
        father.rsum = max(rson.rsum, lson.rsum + rson.sum);
        father.dat = max(max(father.lsum, father.rsum), lson.rsum + rson.lsum);
        father.dat = max(max(lson.dat, rson.dat), father.dat);
        return father;
    }
}seg;
int n, m;
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &seg.arr[i]);
    }
    seg.build(1, 1, n);
    for(int i = 0; i < m; i ++){
        int a, b, c;
        scanf("%d", &a);
        if(a == 1){
            scanf("%d%d", &b, &c);
            if(b > c){
                swap(b, c);
            }
            NODE re = seg.query(1, b, c);
            printf("%d\n", re.dat);
        }
        else{
            scanf("%d%d", &b, &c);
            seg.change(1, b, b, c);
        }
    }
    return 0;
}