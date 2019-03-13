#include <bits/stdc++.h>
using namespace std;
const int N=100100;
int a[N],n,i,ans,sum;
int main()
{
    cin>>n;
    for (i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    int sm=a[n>>1 | 1];
    for (i=1;i<=n;i++)
        ans=ans+abs(a[i]-sm);
    cout<<ans;
    return 0;
}
