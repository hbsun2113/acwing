#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <bitset>
using namespace std;
int n;
/**
 这样的bfs
 是搞不定这个题目的
 感觉A*应该可以
 那么我们来讨论一下 A* 算法关于这个题目的解法吧
 我也找不到题解，所以我只能自己瞎搞
 等一下仿佛可以不 A*
 莫得了不A* TLE
 啥是A* 算法呢？
 如果给定一个目标的状态，需要求出从初态到目标状态的最小代价
 那么优先队列的这个“优先策略”显然是不完善的
 一个状态的当前状态最小，只能说明启始状态到到该状态的代价很小
 而在未来的搜索中，从该状态到目标状态可能会花费很大的代价
 为了提高搜索的效率，那么我们应该设计一个“估值”函数，以任意“状态”输入
 计算出从当前状态到目标状态所需代价的估计值
 
 设当前状态到目标状态所需要代价的估计值为f(state)
 设在未来的搜索中，实际求出的从当前状态state到目标状态的最小代价g(state)
 对于任意的state,应该有f(state) <= g(state)
 
 我得尝试一下 A*
 **/
typedef struct NODE
{
    int num;
    bitset<105>bt;
    int len;
}node;
queue<node>que;
node result;
void bfs(node a)
{
    while(!que.empty())
    {
        que.pop();
    }
    que.push(a);
    while(!que.empty())
    {
        node begins = que.front();
        que.pop();
        if(begins.len > result.len || begins.len > 10)
            continue;
        if(begins.num == n)
        {
            if(result.len > begins.len)
            {
                result = begins;
            }
            return ;
        }
                for(int j = begins.num; j != 0; j --)
                {
                    if(begins.bt[j] == 1)
                    {
                        int num = begins.num + j;
                        if(num <= n && begins.len + 1 < result.len && begins.bt[num] == 0)
                        {
                            node ends = begins;
                            ends.num = num;
                            ends.bt[num] = 1;
                            ends.len = ends.len + 1;
                            if(ends.num == n)
                            {
                                result = ends;
                                return ;
                            }
                            que.push(ends);
                        }
                        else if(num < begins.num)
                        {
                            break;
                        }
                    }
                }
            
        }
    }
int main()
{
    while(~scanf("%d", &n) && n)
    {
        node begins;
        begins.num = 1;
        begins.bt[1] = 1;
        begins.len = 1;
        result.len = 11;
        result.num = 1;
        result.bt = 0;
        bfs(begins);
        for(int i = 1; i <= n; i ++)
        {
            if(result.bt[i] == 1)
                printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}


