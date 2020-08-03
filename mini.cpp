#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=20005;
struct Edge{
    int u,v,w;
}edge[maxn];
int f[maxn],sz[maxn];
int T,n;
int get(int x){
    return f[x]==x?x:f[x]=get(f[x]);
}
bool cmp(Edge a,Edge b) {
    return a.w<b.w;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
            sz[i]=1;
            f[i]=i;
        }
        f[n]=n;
        sz[n]=1;
        long long ans=0;
        sort(edge+1,edge+n,cmp);
        for (int i=1;i<n;i++) {
            int fu=get(edge[i].u),fv=get(edge[i].v);
            if (fu!=fv){
                ans+=1ll*(sz[fu]*sz[fv]-1ll)*(edge[i].w+1ll);
                sz[fu]+=sz[fv];
                f[fv]=fu;
                ans+=edge[i].w;
            }
        }
        printf("%lld\n",ans);
    }
}