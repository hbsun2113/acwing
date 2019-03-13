#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int n;
vector<int>vec;
vector<int>re;
int vids[20];
void dfs(int step, int num)
{
    //printf("step = %d\n", step);
    for(int i = num; i < vec.size(); i ++)
    {
        if(vids[i] == 0)
        {
            re.push_back(vec[i]);
            vids[i] = 1;
            if(!re.empty())
            {
                for(int j = 0; j < re.size(); j ++)
                    printf("%d ", re[j]);
                printf("\n");
            }
            dfs(step + 1, i);
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
        vec.clear();
        memset(vids, 0, sizeof(vids));
        for(int i = 1; i <= n; i ++)
            vec.push_back(i);
        printf("\n");
        dfs(0, 0);
    }
    return 0;
}

