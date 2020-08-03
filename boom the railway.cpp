#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int saizu=5005;
struct Edge{
	int fr,to,nxt;
	bool key;
}edge[saizu*2];
int n,m,tot,num,head[saizu],dfn[saizu],low[saizu];
bool cmp(Edge a,Edge b){
	return a.fr<b.fr||(a.fr==b.fr&&a.to<b.to);
}
void add(int u,int v){
	tot++;
	edge[tot].fr=u;
	edge[tot].to=v;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void tarjan(int x,int in){
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=edge[i].nxt){
		int y=edge[i].to;
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]) edge[i].key=edge[i^1].key=true;
		}
		else if(i!=(in^1)) low[x]=min(low[x],low[y]);
	}
}
int main(){
	// freopen("in.txt","r",stdin);
	// freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&m);
	tot=1;
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,0);
	for(int i=2;i<=tot;i++){
		if(i%2==1) edge[i].key=false;
		if(edge[i].fr>edge[i].to) swap(edge[i].fr,edge[i].to);
	}
	sort(edge+2,edge+m*2+2,cmp);
	for(int i=2;i<=tot;i++)
		if(edge[i].key) printf("%d %d\n",edge[i].fr,edge[i].to);
	return 0;
}
