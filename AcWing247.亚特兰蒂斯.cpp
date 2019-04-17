#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
/**
 大概知道了扫描线是个啥玩意了
 首先每个矩形都可以看成两条边
 一条是下边，一条是上边
 每条边肯定存在l，r，flag
 l：代表一条边的左边界点
 r：代表一条边的右边界点
 flag:代表下边或者上边，下边为1，上边为-1
 题目给出的是左上角(x1, y1)
           右下角(x2, y2)

 上边为l = x1, r = x2, y = y1, flag = -1
 下边为l = x1, r = x2, y = y2, flag = 1

 处理完成后，针对y的值从小到大排序
 
 因为给出的值会为小数，所以针对l，r进行离散化处理
 那么每次读入一条边后，使用线段树对其进行维护
 即区间更新[l, r] + flag
 
 ll re = 0;
 for(int i = 1; i < 2 * N; i ++){
 re += (h[i] - h[i - 1]) * ∑(len);
 ///∑(len)的含义为当前的区间里面所有的值不为0的总和
 }
 注意线段树上的每个点代表的不是单点，是相邻的段
 比如节点1 代表的就是arr[2] - arr[1]
 
 **/
const int MAXN = 100 + 5;
struct NODE{
    int l, r;
    double y;
    int flag;
}arr[MAXN << 1];
struct MYINT{
    double x1, x2, y1, y2;
}brr[MAXN << 1];
vector<double>vec;
int acfinds(double num)
{
    return lower_bound(vec.begin(), vec.end(), num) - vec.begin() + 1;
}
bool cmp(const NODE &a, const NODE &b){
    return a.y < b.y;
}
struct SEGTREE{
    struct TREE_NODE{
        int l, r;
        double cnt, len;
    }tree[MAXN << 2];
    void Init(){
        memset(tree, 0, sizeof(tree));
    }
    void build(int root, int l, int r){
        tree[root].l = l;
        tree[root].r = r;
        tree[root].cnt = tree[root].cnt = 0;
        if(l == r){
            return ;
        }
        int mid = (l + r) >> 1;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
    }
    void push_down(int root){///cnt不下压
        if(tree[root].cnt){
                ///假设更新的是1 2，实际上更新的是两个点
                tree[root].len = vec[tree[root].r] - vec[tree[root].l - 1];///长度就是3 - 0
        }
        else if(tree[root].l == tree[root].r){
            tree[root].len = 0;
        }
        else{
            tree[root].len = tree[root << 1].len + tree[root << 1 | 1].len;
        }
    }
    void update(int root, int l, int r, int value){
        int mid = (tree[root].l + tree[root].r) >> 1;
        if(tree[root].l == l && tree[root].r == r){
            tree[root].cnt += value;
            push_down(root);
            return ;
        }
        else if(r <= mid){
            update(root << 1, l, r, value);
        }
        else if(l > mid){
            update(root << 1 | 1, l, r, value);
        }
        else{
            update(root << 1, l, mid, value);
            update(root << 1 | 1, mid + 1, r, value);
        }
        push_down(root);
    }
}seg;
int n;
int main(){
    int step = 0;
    while(~scanf("%d", &n) && n){
        step ++;
        seg.Init();
        vec.clear();
        memset(arr, 0, sizeof(arr));
        memset(brr, 0, sizeof(brr));
        int num = 0;
        for(int i = 0; i < n; i ++){
            scanf("%lf%lf%lf%lf", &brr[i].x1, &brr[i].y1, &brr[i].x2, &brr[i].y2);
            vec.push_back(brr[i].x1);
            vec.push_back(brr[i].x2);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(),vec.end()),vec.end());
        for(int i = 0; i < n; i ++){
            arr[num].l = acfinds(brr[i].x1);
            arr[num].r = acfinds(brr[i].x2) - 1;
            arr[num].y = brr[i].y1;
            arr[num].flag = 1;
            ++ num;
            arr[num].l = acfinds(brr[i].x1);
            arr[num].r = acfinds(brr[i].x2) - 1;
            arr[num].y = brr[i].y2;
            arr[num].flag = -1;
            ++ num;
        }
        sort(arr, arr + num, cmp);
        seg.build(1, 1, num);
        seg.update(1, arr[0].l, arr[0].r, arr[0].flag);
        double re = 0;
        for(int i = 1; i < num; i ++){
            re += ((arr[i].y - arr[i - 1].y) * (seg.tree[1].len));
            seg.update(1, arr[i].l, arr[i].r, arr[i].flag);
        }
        printf("Test case #%d\n", step);
        printf("Total explored area: %.2f\n\n", re);
    }
    return 0;
}

