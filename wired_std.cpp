#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000005;
int cpt[maxn],prt[maxn],pos[maxn],n,m;
long long f[2][maxn];
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        scanf("%d",&prt[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&cpt[i]);
    sort(cpt+1,cpt+1+n);
    sort(prt+1,prt+1+m);
    for(int i=1;i<=n;i++) 
        pos[i]=lower_bound(prt+1,prt+1+m,cpt[i])-prt;
    memset(f,0x3f,sizeof(f));
    for (int i=0;i<=m;i++) 
        f[0][i]=0;
    int p=0,q=1,l,r,u=0,v=m;
    for(int i=1;i<=n;i++){
        l=max(1,pos[i]-n);
        r=min(m,pos[i]+n);
        p^=1,q^=1;
        for(int j=l;j<=r;j++)
            f[p][j]=min(f[p][j-1],f[q][min(j-1,v)]+abs(cpt[i]-prt[j]));
        for(int j=u;j<=v;j++)
            f[q][j]=0x3f3f3f3f;
        u=l,v=r;
    }
    printf("%lld\n",f[p][r]);
    return 0;
}