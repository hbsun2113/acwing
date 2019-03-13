#include <bits/stdc++.h>
using namespace std;
/**
 首先先考虑不是环的情况下
 那么就是普通的均匀分牌问题
 那么最少次数就是互相给牌
 if(hang[i] < t / n)
 hang[i + 1] -= (t / n - hang[i]), hang[i] += (t / n - hang[i]);
 else
 hang[i + 1] += (hang[i] - t / n), hang[i] -= (hang[i] - t / n);
 (假设hang数组内的值不发生变化，注意不要从0开始，数据是从1开始的，哭了)
 第一种情况下的状态
 hang[1] = hang[1] - (t / n - hang[0]) = hang[1] + hang[0] - t / n;
 第二种情况下的状态
 hang[1] = hang[1] + (hang[0] - t / n) = hang[1] + hang[0] - t / n; 
 
 第一次的移动次数为abs(t / n - hang[0]);
 第二次的移动次数为abs(t / n - hang[1] - hang[0] + t / n);
                   abs(2 * t / n - (hang[1] + hang[0]));
 所以可得第i次移动的次数为abs(i * t / n - sum(hang[i - 1]));
        那么可以拆分成abs((t / n - hang[0]) + (t / n - hang[1]) + ...... + (t / n - hang[i]));
        预先处理将数组变成 t / n - hang[i]
        那么求一个前缀和就可以得到每次移动的步数

 如果是环形的话，存在相邻的交换给的话
 肯定不是最优解，最优解肯定只存在于不互相给的情况下
 因为比如a b c d e 是个环 a -> c b -> e，那么实际上
 这肯定不是最优解
 因为可以通过b -> c , a -> e来构造一个更优秀的答案
 所以最优解只存在于不互相给的情况下
 那么就选择一个不交换的点，将其转换成普通的均匀分牌问题
 那么就重新选择出了一个非环的序列
 那么如何选择这个不交换的点
 假设该点为k
 取k为原点
 那么k就变成了基点，那么我们先求出了全部的sum[i]的值
 k ~ n
 sum[k + 1] - sum[k]
 sum[k + 2] - sum[k + 1]
 ....
 过了n之后,因为过了n后,sum[0] + sum[n] - sum[k]
 构成了新的序列的前缀和
 sum[n] + sum[0] - sum[k]
 sum[n] + sum[k] - sum[k]
 
 那么我们要寻找一个合适的k值
 因为sum[n] + sum[0] - sum[k] or sum[k + 1] - sum[k]
 就是一维上的一个求距离的公式
 那么结论就是 取sum[k]的值为sum[1 ~ n]中的中位数
 **/
typedef long long ll;
const int MAXN = 100000 + 5;
int hang[MAXN];
int lie[MAXN];
ll hang_sum[MAXN];
ll lie_sum[MAXN];
struct NODE
{
    ll num;
    ll sum;
};
bool cmp(const NODE &a, const NODE &b)
{
    return a.sum < b.sum;
}
int n, m, t;
void Init()
{
    memset(hang, 0, sizeof(hang));
    memset(lie, 0, sizeof(lie));
    memset(hang_sum, 0, sizeof(hang_sum));
    memset(lie_sum, 0, sizeof(lie_sum));
}
void ycl()
{
    for(int i = 1; i <= n; i ++)
    {
        hang[i] = hang[i] - t / n;
    }
    for(int i = 1; i <= m; i ++)
    {
        lie[i] = lie[i] - t / m;
    }
    hang_sum[0] = hang[0];
    for(int i = 1; i <= n; i ++)
    {
        hang_sum[i] = hang_sum[i - 1] + hang[i];
    }
    lie_sum[0] = lie[0];
    for(int i = 1; i <= m; i ++)
    {
        lie_sum[i] = lie_sum[i - 1] + lie[i];
    }
}
pair<ll, ll> hang_acfinds()
{
    vector<NODE>vec;
    vec.clear();
    for(int i = 1; i <= n; i ++)
        {
            NODE temp;
            temp.num = i;
            temp.sum = hang_sum[i];
            vec.push_back(temp);
        }
    sort(vec.begin(), vec.end(), cmp);
    return {vec[vec.size() / 2].num, vec[vec.size() / 2].sum};
}
pair<ll, ll> lie_acfinds()
{
    vector<NODE>vec;
    vec.clear();
    for(int i = 1; i <= m; i ++)
        {
            NODE temp;
            temp.num = i;
            temp.sum = lie_sum[i];
            vec.push_back(temp);
        }
    sort(vec.begin(), vec.end(), cmp);
    return {vec[vec.size() / 2].num, vec[vec.size() / 2].sum};
}
ll result_hang(pair<ll, ll> num)
{
    ll re = 0;
    for(int i = 1; i <= num.first; i ++)
        re += abs(hang_sum[i] + hang_sum[n] - num.second);
    for(int i = num.first + 1; i <= n; i ++)
        re += abs(hang_sum[i] - num.second);
    return re;
}
ll result_lie(pair<ll, ll> num)
{
    ll re = 0;
    for(int i = 1; i <= num.first; i ++)
        re += abs(lie_sum[i] + lie_sum[m] - num.second);
    for(int i = num.first + 1; i <= m; i ++)
        re += abs(lie_sum[i] - num.second);
    return re;
}
int main()
{
    while(~scanf("%d%d%d", &n, &m, &t))
    {
        Init();
        for(int i = 0; i < t; i ++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            hang[a] ++;
            lie[b] ++;
        }
        bool flag1, flag2;
        flag1 = flag2 = false;
        ycl();
        ll re1, re2;
        if(t % n == 0)///在行的情况下，t个能被整除，才存在解
        {
            flag1 = true;
            pair<ll, ll>num;
            num = hang_acfinds();
            re1 = result_hang(num);
        }
        if(t % m == 0)
        {
            flag2 = true;
            pair<ll, ll>num;
            num = lie_acfinds();
            re2 = result_lie(num);
        }
        if(flag1 && flag2)
        {
            printf("both %lld\n",re1 + re2);
        }
        else if(flag1)
        {
            printf("row %lld\n", re1);
        }
        else if(flag2)
        {
            printf("column %lld\n", re2);
        }
        else
        {
            printf("impossible\n");
        }
    }
    return 0;
}

