#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define res int 
#define LL long long
#define inf 0x3f3f3f3f
inline int read(){
int s=0,w=1;
char ch=getchar();
while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
const int N=20;
int n,m,cnt,p,ans=inf,tmp,tot,c[N][N],tar[N][N],vis[N],level[N],d[N];
inline bool cmp(int a,int b){
    return c[p][a]<c[p][b];
}
inline void dfs(int num,int node){
    if(cnt==n){
        ans=min(ans,tot);
        return;
    }
    for(res i=num;i<=cnt;i++){
        if((tot+tmp*level[vis[i]])>=ans)return;
        for(res j=node;j<=d[vis[i]];j++)
            if(!level[tar[vis[i]][j]]){
                cnt++;
                vis[cnt]=tar[vis[i]][j];
                tmp-=c[vis[cnt]][tar[vis[cnt]][1]];
                tot+=c[vis[i]][vis[cnt]]*level[vis[i]];
                level[vis[cnt]]=level[vis[i]]+1;
                dfs(i,j+1);
                tmp+=c[vis[cnt]][tar[vis[cnt]][1]];
                tot-=c[vis[i]][vis[cnt]]*level[vis[i]];
                level[vis[cnt]]=0;
                cnt--;
            }
        node=1;
    }
}
int main(){
    n=read(),m=read();
    for(res i=1;i<=n;i++)
        for(res j=1;j<=n;j++)c[i][j]=inf;
    for(res i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        if(c[u][v]==inf)tar[u][++d[u]]=v,tar[v][++d[v]]=u;
        c[v][u]=c[u][v]=min(c[u][v],w);
    }
    for(res i=1;i<=n;i++){
        p=i;
        sort(tar[i]+1,tar[i]+1+d[i],cmp);
        tmp+=c[i][tar[i][1]];
    }
    for(res i=1;i<=n;i++){
        tot=0,cnt=1,vis[1]=i,tmp-=c[i][tar[i][1]],level[i]=1;
        dfs(1,1);
        level[i]=0,tmp+=c[i][tar[i][1]];
        printf("%d\n",ans);
    }
    return 0;
}