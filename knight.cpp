//有向无环图中，两条不相交的路径
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=205,maxm=5005;
int n,m,a,aa,b,bb,tot,cnt;
long long f[maxn][maxn],g[maxn];
int in[maxn],tp[maxn];
int to[maxm],val[maxm],nxt[maxm],head[maxn];
void add(int u,int v){
	tot++;
	to[tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
	in[v]++;
}
void topo(){
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(in[i]==0) q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		tp[++cnt]=x;
		for(int i=head[x];i;i=nxt[i]){
			int y=to[i];
			if(--in[y]==0) q.push(y);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	topo();
	for(int i=1,u;i<=n;i++){
		u=tp[i],f[u][u]=1;
		for(int j=i,v;j<=n;j++){
			v=tp[j];
			for(int k=head[v];k;k=nxt[k])
				f[u][to[k]]+=f[u][v];
		}
	}
	scanf("%d%d%d%d",&a,&aa,&b,&bb);
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n;j++){
	// 		printf("%d ",f[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// for(int i=1;i<=n;i++)
	// 	printf("%d",tp[i]);
	for(int i=1,u;i<=n;i++){
		u=tp[i];
		g[u]=f[a][u]*f[b][u];
		for(int j=1,v;j<i;j++){
			v=tp[j];
			g[u]-=g[v]*f[v][u]*f[v][u];
		}
	}
	// for(int i=1;i<=n;i++)
	// 	printf("%lld ",g[i]);
	long long ans=f[a][aa]*f[b][bb];
	for(int i=1,u;i<=n;i++){
		u=tp[i];
		ans-=g[u]*f[u][aa]*f[u][bb];
	}
	printf("%lld",ans);
	return 0;
}