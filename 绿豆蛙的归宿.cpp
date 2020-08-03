#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MaxN = 100005;
struct Edge{
	int nextEdge, destinationVertex, edgeValue;
}edge[MaxN * 2];
int n, m, tot, head[MaxN], outdu[MaxN];
double f[MaxN];
bool vis[MaxN];
inline void AddEdge(int u,int v,int w){
	tot++;
	edge[tot].nextEdge = head[u];
	edge[tot].destinationVertex = v;
	edge[tot].edgeValue = w;
	outdu[u]++;
	head[u] = tot;
}
void DFS(int x){
	if(x == n){f[x] = 0; return;}
	if(vis[x]) return;
	vis[x] = true;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destinationVertex;
		DFS(y);
		f[x] += (double)((f[y] + edge[i].edgeValue) / outdu[x]);
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(u,v,w);
	}
	DFS(1);
	printf("%.2lf\n",f[1]);
	return 0;
}
/* 绿豆蛙的归宿
一个有向图，有很多条路径，于是难以线性地叠加期望。
考虑用类似树形DP的方法解决，发现难以下手：问题在于没有合适的起始点。
可以命f[i]表示从点i到终点的路径长度的期望——f[n]=0，即自己到自己距离为0。
这样就可以使用DFS以起点为搜索入口，从终点往回累加期望。*/