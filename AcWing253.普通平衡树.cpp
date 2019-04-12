#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int SIZE = 100000 + 5;
struct TREE{
    int tot, root, INF = 0x7fffffff;
    struct Treap{
        int l, r;///左右子树在数组中的下标
        int val, dat;///单个点出现的次数，平衡树的权值
        int cnt, size;///副本数，子树大小
    }arr[SIZE << 2];
    int New(int val){
        arr[++ tot].val = val;
        arr[tot].dat = -rand();
        arr[tot].cnt = arr[tot].size = 1;
        return tot;
    }
    void Update(int p){
        arr[p].size = arr[arr[p].l].size + arr[arr[p].r].size + arr[p].cnt;
    }
    void Init(){
        for(int i = 0; i < (SIZE << 2); i ++){
            arr[i].dat = -INF;
        }
    }
    void Build(){
        New(-INF), New(INF);///两个初始的节点，+∞ -∞
        ///因为空节点的dat是0，那么旋转的过程中，如果是0的话，就会被旋转上去,那么就发生了错误
        root = 1; arr[1].r = 2;///将初始节点连接起来
        Update(root);///更新根节点
    }
    /**
     假设Treap满足BST的性质，符合左小右大
     那么考虑在符合左小右大的情况下，进行Treap的旋转
     将左儿子旋转到父亲节点
     int q = arr[p].l;
     arr[p].l = arr[q].r;
     arr[q].r = p;
     p = q;///本质是左儿子的父亲节点的父亲节点的左儿子改变为q
     
     lyd 利用了C++引用的特点，所以代码来得更简洁
     **/
    void Zig(int &p){///左旋，将左儿子旋转到父
        int q = arr[p].l;///保存左儿子的编号
        arr[p].l = arr[q].r;///将父节点下移动的过程中，Treap符合BST的性质
        ///那么该原父亲节点的val值肯定大于该左节点，那么父亲节点得连接到该向上旋转的
        ///左子节点的右节点上，那么原来的左子节点的右子树就必须连接到向下旋转的父亲
        ///节点的左儿子节点上，所以可得arr[p].l = arr[q].r
        arr[q].r = p;
        ///那么将父亲节点连接到原来的左子节点的右节点上
        p = q;///然后将原来的左儿子连接到，爷爷节点的左节点上 或者 右节点上
        ///int &p 就可以代表爷爷节点的l 或者 r的属性所对应的空间
        Update(arr[p].r);///旋转后进行数据的更新
        Update(p);
    }
    void Zag(int &p){///右旋，将右儿子选择到父
        int q = arr[p].r;///保存右儿子的编号;
        arr[p].r = arr[q].l;///以下与上述的Zig过程类似
        arr[q].l = p;
        p = q;
        Update(arr[p].l);///旋转后进行数据的更新
        Update(p);
    }
    void Insert(int &p, int val){
        ///因为采用了引用，所以在递归过程中的数值也发生了改变
        ///所以就会一层一层的向上，所以说在不断的Zig或Zag的过程中
        ///会保证val符合BST的性质,dat符合最大堆的性质
        if(p == 0){///发现当前没有这个对应的值，那么就更新一个值
            p = New(val);
            return ;
        }
        if(val == arr[p].val){///发现当前有对应的值，就更新当前对应的值的副本大小
            arr[p].cnt ++, Update(p);
            return ;
        }
        if(val < arr[p].val){
            Insert(arr[p].l, val);///插入完成后，每发现不符合就旋转
            if(arr[p].dat < arr[arr[p].l].dat){
                Zig(p);
            }
        }
        else{
            Insert(arr[p].r, val);///插入完成后，发现不符合就旋转
            if(arr[p].dat < arr[arr[p].r].dat){
                Zag(p);
            }
        }
        Update(p);
    }
    void Remove(int &p, int val){
        if(p == 0){
            return ;///没有该节点
        }
        if(val == arr[p].val){
            if(arr[p].cnt > 1){
                ///如果当前的副本数是大于1的话，Treap的平衡结构是不需要发生改变
                arr[p].cnt --;///所以对arr[p].cnt的值进行修改即可
                Update(p);///然后对p的值进行更新
                return ;///删除完毕后return结束
            }
            if(arr[p].l || arr[p].r){///如果当前的副本数为1且该点不是叶子结点需要更新
                ///那么就把节点向下旋转，旋转到根节点，进行更新
                if(arr[p].r == 0 || arr[arr[p].l].dat > arr[arr[p].r].dat){
                    Zig(p);
                    Remove(arr[p].r, val);
                }
                else{
                    Zag(p);
                    Remove(arr[p].l, val);
                }
                Update(p);///Remove过程结束，更新当前的值
            }
            else p = 0;
            return ;
        }
        val < arr[p].val ? Remove(arr[p].l, val) : Remove(arr[p].r, val);///判断删除的点在左还是右子树
        Update(p);///更新对应的数值
    }
    ///然后下面的就是常规的树上跑搜素(递归), 不会的退役一下
    int GetRankbyVal(int p, int val){
        if(p == 0) return 0;
        if(val == arr[p].val) return arr[arr[p].l].size + 1;
        if(val < arr[p].val){
            return GetRankbyVal(arr[p].l, val);
        }
        return GetRankbyVal(arr[p].r, val) + arr[arr[p].l].size + arr[p].cnt;
    }
    int GetValbyRank(int p, int rank){
        if(p == 0) return INF;
        if(arr[arr[p].l].size >= rank){
            return GetValbyRank(arr[p].l, rank);
        }
        if(arr[arr[p].l].size + arr[p].cnt >= rank){
            return arr[p].val;
        }
        return GetValbyRank(arr[p].r, rank - arr[arr[p].l].size - arr[p].cnt);
    }
    int GetPre(int val){
        int ans = 1;///a[1].val == - INF
        int p = root;
        while(p){
            if(val == arr[p].val){
                if(arr[p].l > 0){
                    p = arr[p].l;
                    while(arr[p].r > 0){
                        p = arr[p].r;
                    }
                    ans = p;
                }
                break;
            }
            if(arr[p].val < val && arr[p].val > arr[ans].val){
                ans = p;
            }
            p = val < arr[p].val ? arr[p].l : arr[p].r;
        }
        return arr[ans].val;
    }
    int GetNext(int val){
        int ans = 2;
        int p = root;
        while(p){
            if(val == arr[p].val){
                if(arr[p].r > 0){
                    p = arr[p].r;
                    while(arr[p].l > 0){
                        p = arr[p].l;
                    }
                    ans = p;
                }
                break;
            }
            if(arr[p].val > val && arr[p].val < arr[ans].val){
                ans = p;
            }
            p = val > arr[p].val ? arr[p].r : arr[p].l;
        }
        return arr[ans].val;
    }
}tree;
int main()
{
    int n;
    scanf("%d", &n);
    tree.Init();
    tree.Build();
    for(int i = 0; i < n; i ++){
        int opt, x;
        scanf("%d%d", &opt, &x);
        if(opt == 1){
            tree.Insert(tree.root, x);
        }
        if(opt == 2){
            tree.Remove(tree.root, x);
        }
        if(opt == 3){
            printf("%d\n", tree.GetRankbyVal(tree.root, x) - 1);
        }
        if(opt == 4){
            printf("%d\n", tree.GetValbyRank(tree.root, x + 1));
        }
        if(opt == 5){
            printf("%d\n", tree.GetPre(x));
        }
        if(opt == 6){
            printf("%d\n", tree.GetNext(x));
        }
    }
    return 0;
}

