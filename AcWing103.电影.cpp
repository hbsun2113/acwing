#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
/**
 准确的说是离散化 + map
 我试试复杂度
 离散化+map = 歇逼
 离散化+数组标记法
 **/
const int MAXN = 500000 + 5;
int arr[MAXN];
int vids[MAXN];
struct node{
    int b, c;
}arrs[MAXN];
int n, m;
vector<int>vec;
void discrete()///离散化
{
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}
int query(int x)///查询离散化后的映射
{
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin();
}
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%d", &arr[i]), vec.push_back(arr[i]);
    scanf("%d", &m);
    for(int i = 0; i < m; i ++)
        scanf("%d", &arrs[i].b), vec.push_back(arrs[i].b);
    for(int i = 0; i < m; i ++)
        scanf("%d", &arrs[i].c), vec.push_back(arrs[i].c);
    discrete();
    for(int i = 0; i < n; i ++)
        vids[query(arr[i])] ++;
    int re_num = 0;
    int re_sum = -1;
    int re_sum1 = -1;
    for(int i = 0; i < m; i ++)
    {
        if(vids[query(arrs[i].b)] > re_sum)
        {
            re_sum = vids[query(arrs[i].b)];
            re_sum1 = vids[query(arrs[i].c)];
            re_num = i;
        }
        else if(vids[query(arrs[i].b)] == re_sum)
        {
            if(vids[query(arrs[i].c)] > re_sum1)
            {
                re_sum1 = vids[query(arrs[i].c)];
                re_num = i;
            }
        }
    }
    //printf("%d %d %d\n", re_num, vids[query(arrs[i].b)], vids[query(arrs[i].c)]);
    printf("%d\n", re_num + 1);
    return 0;
}


