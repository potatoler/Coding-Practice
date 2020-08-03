#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=16005;
struct Edge{
	int nxt,to;
}edge[maxn*2];
int n,a[maxn],head[maxn],tot,f[maxn],ans;
void add(int u,int v){
	edge[++tot].nxt=head[u];
	edge[tot].to=v;
	head[u]=tot;
}
void dfs(int cur,int fa){
	f[cur]=a[cur];
	for(int i=head[cur];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa){
			dfs(v,cur);
			f[cur]+=max(0,f[v]);
		}
	}
	ans=max(ans,f[cur]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}