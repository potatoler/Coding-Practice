#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100000;
int n,m,tot,t1,t2,ansfr,ansdis=0x3f3f3f3f,ansto=maxn;
bool ser[maxn];
int cpt[maxn],dis[maxn],t[maxn],head[maxn];
struct Edge{
	int to,val,nxt;
}edge[maxn*4];
void add(int u,int v,int w){
	tot++;
	edge[tot].to=v;
	edge[tot].val=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}
void scn(int x){
	for(int i=head[x];i;i=edge[i].nxt){
		if(ser[edge[i].to]){
			if(dis[x]>edge[i].val) dis[x]=edge[i].val,t[x]=edge[i].to;
			else if(dis[x]==edge[i].val) t[x]=min(t[x],edge[i].to);
		}
	}
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	scanf("%d",&t1);
	for(int i=1;i<=t1;i++){
		scanf("%d",&cpt[i]);
		ser[cpt[i]]=false;
		t[cpt[i]]=cpt[i];
	}
	scanf("%d",&t2);
	for(int i=1;i<=t2;i++){
		int tmp;
		scanf("%d",&tmp);
		ser[tmp]=true;
	}
	for(int i=1;i<=t1;i++){
		int x=cpt[i];
		scn(x);
		if(ansdis>dis[x]) ansfr=x,ansdis=dis[x],ansto=t[x];
		else if(ansdis==dis[x]) ansfr=min(ansfr,x),ansdis=dis[x],ansto=t[ansfr];
	}
	printf("%d %d %d\n",ansdis,ansfr,ansto);
}
