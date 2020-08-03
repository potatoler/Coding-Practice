#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<queue>
using namespace std;
const int MaxN = 305;
struct Edge{
	int destination, value, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int distance, father;
	bool vis;
}vertex[MaxN];
int head[MaxN], tot, n, m, s, t, ans = INT_MAX, mx[MaxN];
#define des edge[i].destination

inline void AddEdge(int u, int v, int w){
	tot++;
	edge[tot].destination = v;
	edge[tot].nextEdge = head[u];
	edge[tot].value = w;
	head[u] = tot;
}

void DFS(int x, int fa){
	vertex[x].father = fa;
	for(int i=head[x];i;i=edge[i].nextEdge){
		if(des == fa) continue;
		vertex[des].distance = vertex[x].distance + edge[i].value;
		DFS(des, x);
	}
}

void Update(int x, int fa, int cur){
	mx[cur] = max(mx[cur], vertex[x].distance);
	for(int i=head[x];i;i=edge[i].nextEdge){
		if(des == fa) continue;
		if(vertex[des].vis) continue;
		vertex[des].distance = vertex[x].distance + edge[i].value;
		Update(des, x, cur);
	}
}

void Diameter(){
	DFS(1,0);
	for(int i=1;i<=n;i++)
		if(vertex[i].distance > vertex[s].distance) s = i;
	vertex[s].distance = 0;
	DFS(s,0);
	for(int i=1;i<=n;i++)
		if(vertex[i].distance > vertex[t].distance) t = i;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u, v, w;
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	Diameter();
	for(int i=t;i;i=vertex[i].father)
		vertex[i].vis = true;
	for(int i=t;i;i=vertex[i].father){
		Update(i, vertex[i].father, i);
		mx[i] -= vertex[i].distance;
	}
	int l=t, r=t;
	for(1;l;l=vertex[l].father){
		while(vertex[r].distance - vertex[l].distance > m) r = vertex[r].father;
		int res = max(vertex[t].distance - vertex[r].distance, vertex[l].distance);
		for(int i=r;i;i=vertex[i].father){
			res = max(res, mx[i]);
			if(i == l) break;
		}
		ans = min(ans, res);
	}
	printf("%d",ans);
	return 0;
}