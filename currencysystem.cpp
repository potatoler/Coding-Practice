#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int f[25005],a[105];
int n,T,ans;
int main(){
    scanf("%d",&T);
    while(T--){
        memset(f,0,sizeof(f));
        scanf("%d",&n);
        ans=n;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        f[0]=1;
        for(int i=1;i<=n;i++){
            if(f[a[i]]){
                ans--;
                continue;
            }
            for(int j=a[i];j<=a[n];j++)
                f[j]=f[j]|f[j-a[i]];
        }
        printf("%d\n",ans);
    }
    return 0;
}