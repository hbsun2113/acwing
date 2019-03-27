#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
/**
玄学ac，我也不会证明
所以2333
**/
int c, l;
typedef struct COW
{
    int minspf, maxspf;
}cow;
cow arr[2505];
int vids[1005];
bool cmp(const cow &a, const cow & b)
{
    return a.minspf > b.minspf;
}
int main()
{
    while(~scanf("%d%d", &c, &l))
    {
        memset(arr, 0, sizeof(arr));
        memset(vids, 0, sizeof(vids));
        for(int i = 0; i < c; i ++)
        {
            scanf("%d%d", &arr[i].minspf, &arr[i].maxspf);
        }
        for(int i = 0; i < l; i ++)
        {
            int cost, num;
            scanf("%d%d",&num, &cost);
            vids[num] += cost;
        }
        sort(arr, arr + c, cmp);
        int sum = 0;
        for(int i = 0; i < c; i ++)
        {
            for(int j = arr[i].maxspf; j >= arr[i].minspf; j --)
            {
                if(vids[j] != 0)
                {
                    vids[j] --;
                    sum ++;
                    break;
                }
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}
