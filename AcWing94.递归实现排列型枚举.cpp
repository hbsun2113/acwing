#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
int n;
int vids[15];
vector<int>re;
void dfs(int step)
{
    if(step == n)
    {
        for(int i = 0; i < re.size(); i ++)
            printf("%d ", re[i]);
        printf("\n");
        return ;
    }
    for(int i = 1; i <= n; i ++)
    {
        if(!vids[i])
        {
            re.push_back(i);
            vids[i] = 1;
            dfs(step + 1);
            vids[i] = 0;
            re.pop_back();
        }
    }
}
int main()
{
    while(~scanf("%d", &n))
    {
        re.clear();
        memset(vids, 0, sizeof(vids));
        dfs(0);
    }
}

