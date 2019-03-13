#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
priority_queue<ll, vector<ll>, greater<ll>> ques;  // 小顶堆
priority_queue<ll, vector<ll>, less<ll>> que;     // 大顶堆
/**
 那么考虑
 问题在于维护大根堆跟小根堆的个数一个为n / 2 + 1 , n / 2
 这样每次提取大根堆的top，就是要查询的答案了
 
 if(que.empty())que.push(num);
 if(que.empty())
    if(num > ques.top())
 {
 ques.push(num);
 que.push(que.top());
 ques.pop();
 }
 **/
void Init()
{
    while(!que.empty())
        que.pop();
    while(!ques.empty())
        ques.pop();
}
int t;
int main()
{
    scanf("%d", &t);
    while(t --)
    {
        int a, n;
        scanf("%d%d", &a, &n);
        Init();
        vector<ll>vec;
        vec.clear();
        for(int i = 1; i <= n; i ++)
        {
            ll num;
            scanf("%lld", &num);
            if(!ques.empty())
            {
                bool flag = false;
                if(num > ques.top())
                {
                    que.push(ques.top());
                    ques.pop();
                    ques.push(num);
                    flag = true;
                }
                if(!flag)
                    que.push(num);
            }
            else
            {
                que.push(num);
            }
            while(que.size() > i / 2 + 1)
            {
                ques.push(que.top());
                que.pop();
            }
            while(ques.size() > i / 2)
            {
                que.push(ques.top());
                ques.pop();
            }
            if(i & 1)
            {
                vec.push_back(que.top());
            }
        }
        printf("%d %d\n", a, (n + 1) / 2);
        for(int i = 0; i < vec.size(); i ++)
        {
            if(i % 10 == 0 && i)
                printf("\n");
        printf("%lld ", vec[i]);
            
        }
        printf("\n");
    }
    return 0;
}

