#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=105;
struct Edge{
	int to,a,nxt;
}edge[maxn*2];
int head[maxn],f[maxn][maxn],n,q,tot;
void add(int u,int v,int w){
	edge[++tot].to=v;
	edge[tot].a=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void dfs(int cur,int pre,int sum){
	int son[maxn]={0},cnt=0;
	bool flag=false;
	for(int i=head[cur];i;i=edge[i].nxt){
		if(edge[i].to!=pre){
			flag=true;
			son[++cnt]=i;
			dfs(edge[i].to,cur,edge[i].a);
		}
	}
	if(!flag) return;
	for(int i=1;i<=q;i++){
		for(int j=0;j<=i;j++){
			int tmp=0;
			if(j-1>=0) tmp+=edge[son[1]].a;
			if(i-j-1>=0) tmp+=edge[son[2]].a;
			if(j!=0) f[cur][i]=max(f[cur][i],f[edge[son[1]].to][j-1]+tmp+f[edge[son[2]].to][i-j-1]);
			else f[cur][i]=max(f[cur][i],f[edge[son[2]].to][i-j-1]+tmp);
		}
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0,0);
	printf("%d",f[1][q]);
	return 0;
}