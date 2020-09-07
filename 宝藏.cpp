#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int n, m, g[20][20], f[10000], dis[20], ans=INT_MAX;

inline int Read(){
    int num = 0, op = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') op = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num * op;
}

inline void find(int x){
    for(int i=1;i<=n;i++)
    if((1<<(i-1))&x){
        for(int j=1;j<=n;j++)
        if(((1<<(j-1))&x)==0&&g[i][j]!=INT_MAX)
        {
            if(f[x|(1<<(j-1))]>f[x]+dis[i]*g[i][j])
            {
                int tmp=dis[j];
                dis[j]=dis[i]+1;
                f[x|(1<<(j-1))]=f[x]+dis[i]*g[i][j];
                find(x|(1<<(j-1)));
                dis[j]=tmp;
            }
        } 
    }
}

signed main(){
    n = Read(), m = Read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g[i][j]=INT_MAX;
    for(int i=1;i<=m;i++){
        int u = Read(), v = Read(), z = Read();
        g[u][v] = min(g[u][v], z);
        g[v][u] = min(g[v][u], z);
    }
    for(int o=1;o<=n;o++)
    {
        for(int i=1;i<=n;i++) dis[i]=INT_MAX;
        for(int i=1;i<=(1<<n)-1;i++) f[i]=INT_MAX;
        dis[o]=1;
        f[1<<(o-1)]=0;
        find(1<<(o-1));
        ans = min(ans,f[(1<<n)-1]);
    } 
    printf("%lld",ans);
    return 0;
}
