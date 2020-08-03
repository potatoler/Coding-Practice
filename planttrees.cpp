#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=30003,maxm=100005;
int n,m;
int dis[maxn],head[maxn],tot;
bool vis[maxn];
struct Edge{
	int to,nxt,val;
}edge[maxm];
void add(int u,int v,int w){
	tot++;
	edge[tot].to=v;
	edge[tot].val=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void SPFA(int x){
	queue<int> q;
	q.push(x);
	for(int i=0;i<=n;i++)
		dis[i]=1;
	dis[x]=0,vis[x]=1;
	while(q.size()){
		int y=q.front();
		q.pop();
		vis[y]=0;
		for(int i=head[y];i;i=edge[i].nxt){
			int z=edge[i].to;
			if(dis[z]>dis[y]+edge[i].val){
				dis[z]=dis[y]+edge[i].val;
				if(!vis[z]){
					q.push(z);
					vis[z]=1;
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++) add(n+1,i,0);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(v,u-1,-w);
	}
	for(int i=1;i<=n;i++){
		add(i-1,i,1);
		add(i,i-1,0);
	}
	SPFA(n+1);
	int mn=233333333;
	for(int i=0;i<=n;i++)
		mn=min(mn,dis[i]);
	printf("%d",dis[n]-mn);
	return 0;
}