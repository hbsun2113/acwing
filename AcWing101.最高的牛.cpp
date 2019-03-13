#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
/**
 [思路]:先假设所有的牛都一样高，那么能互相看见的话
 就做从（l， r）的差分，那么+1，这就是相差的高度，
 要考虑重复出现的情况，那么就考虑使用map<pair<int>,int>
 来标记出现的情况，
 最后for循环输出h-arr[i]即可
 **/
map<pair<int, int>, int>M;
int n, p, h, m;
int arr[10000 + 5];
void Init()
{
    M.clear();
    memset(arr, 0, sizeof(arr));
}
int main()
{
    while(~scanf("%d%d%d%d", &n, &p, &h, &m))
    {
        Init();
        for(int i = 0; i < m; i ++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            if(a > b)
                swap(a, b);
            if(M.count(make_pair(a, b)) == 1)
            {
                continue;
            }
            else
            {
                M[make_pair(a, b)] = 1;
                arr[a + 1] += 1;
                arr[b] -= 1;
            }
        }
        for(int i = 1; i <= n; i ++)
        {
            arr[i] += arr[i - 1];
        }
        for(int i = 1; i <= n; i ++)
        {
            printf("%d\n", h - arr[i]);
        }
    }
    return 0;
}


