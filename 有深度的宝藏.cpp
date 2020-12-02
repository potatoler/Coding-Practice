#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long ll;
const int inf=2e9+7;
inline int read(){
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=(p<<3)+(p<<1)+c-'0';c=getchar();}
    return f*p;
}
const int maxn=13;
int n,m,lim,ans=inf,G[maxn][maxn];
int mnval;
int dis[maxn],f[maxn][maxn][1<<maxn][maxn];
//
inline void dfs(int root,int s,int sum,int cnt){
	if(sum+mnval*cnt>=ans)return;
	if(s==lim){
        ans = min(ans, sum);
        return;
    }
    for(int i=1;i<=n;i++){
        if(!(1<<(i-1)&s))continue;
        for(int j=1;j<=n;j++){
            if(!(1<<(j-1)&s)&&G[i][j]<1e9){
                if(f[root][j][1<<(j-1)|s][dis[i]+1]<=sum+dis[i]*G[i][j])continue;
                f[root][j][1<<(j-1)|s][dis[i]+1]=sum+dis[i]*G[i][j];
                dis[j]=dis[i]+1;
                dfs(root, 1<<(j-1)|s,f[root][j][1<<(j-1)|s][dis[i]+1],cnt-1);
            }
        }
    }
}
int main()
{
    n=read(),m=read(),lim=(1<<n)-1;
    memset(G,0x3f,sizeof(G));
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),w=read();
        G[x][y]=G[y][x]=min(G[x][y],w);
        mnval = min(mnval, w);
    }
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++){
//      memset(dis,0,sizeof(dis));
        dis[i]=1;
        dfs(i,1<<(i-1),0, 11);
    }
    printf("%d\n",ans);
    return 0;
}