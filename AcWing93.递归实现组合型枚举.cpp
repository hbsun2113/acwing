#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int n, m;
vector<int>vec;
vector<int>re;
int vids[35];
void dfs(int step, int num)
{
    if(step == m)
    {
        for(int i = 0; i < re.size(); i ++)
            printf("%d ", re[i]);
        printf("\n");
        return ;
    }
    else
    {
        for(int i = num; i < vec.size(); i ++)
        {
            if(!vids[i])
            {
                vids[i] = 1;
                re.push_back(vec[i]);
                dfs(step + 1, i);
                vids[i] = 0;
                re.pop_back();
            }
        }
    }
}
int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        memset(vids, 0, sizeof(vids));
        vec.clear();
        re.clear();
        for(int i = 1; i <= n; i ++)
            vec.push_back(i);
        dfs(0, 0);
    }
    return 0;
}

