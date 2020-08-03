#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=3005;
int n,m,head[maxn],tot,val[maxn],f[maxn][maxn];
struct Edge{
	int to,nxt,w;
}edge[maxn*2];
void add(int u,int v,int w){
	edge[++tot].to=v;
	edge[tot].w=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
int dfs(int u){
	if(u>n-m){
		f[u][1]=val[u];
		return 1;
	}
	int sum=0,son;
	for(int k=head[u];k;k=edge[k].nxt){
		int v=edge[k].to;
		son=dfs(v);
		sum+=son;
		for(int j=sum;j>0;j--){
			for(int i=1;i<=son;i++){
				if(j-i>=0) f[u][j]=max(f[u][j],f[u][j-i]+f[v][i]-edge[k].w);
			}
		}
	}
	return sum;
}
int main(){
	memset(f,-0x3f,sizeof(f));
	scanf("%d%d",&n,&m);
	for(int u=1;u<=n-m;u++){
		int size,v,w;
		scanf("%d",&size);
		for(int j=1;j<=size;j++){
			scanf("%d%d",&v,&w);
			add(u,v,w);
		}
	}
	for(int i=n-m+1;i<=n;i++)
		scanf("%d",&val[i]);
	for(int i=1;i<=n;i++)
		f[i][0]=0;
	dfs(1);
	for(int i=m;i>=1;i--){
		if(f[1][i]>=0){
			printf("%d",i);
			break;
		}
	}
	return 0;
}