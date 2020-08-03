#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int maxn=500005;
int n,m;
struct Edge{
	int to,nxt,val;
}edge[maxn*2];
int head[maxn],dis[maxn],tot;
bool vis[maxn];
void add(int u,int v,int w){
	tot++;
	edge[tot].to=v;
	edge[tot].val=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void spfa(){
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0,vis[1]=1;
	q.push(1);
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=edge[i].nxt){
			int y=edge[i].to,z=edge[i].val;
			if(dis[y]<dis[x-1]+z){
				dis[y]=dis[x-1]+z;
				if(!vis[y]){
					q.push(y);
					vis[y]=1;
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		//add(v,u,w);
	}
	spfa();
	for(int i=1;i<=n;i++)
		printf("%d\n",dis[i]);
	return 0;
}
/*
9 4
1 4 2
4 6 2
8 9 2
3 5 2
*/