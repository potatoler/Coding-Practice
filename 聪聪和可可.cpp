#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
const int MaxN = 1005;
int n, e, c, m, cntEdge;
int head[MaxN], p[MaxN], nextStep[MaxN][MaxN], dis[MaxN][MaxN], degree[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
double f[MaxN][MaxN];
bool visSPFA[MaxN], visDFS[MaxN][MaxN];

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	degree[v]++;
}

inline void SPFA(int x){
	memset(dis[x], 0x3f3f3f3f, sizeof(dis[x]));
	dis[x][x] = 0;
	queue<int>q;
	q.push(x);
	visSPFA[x] = true;
	while(q.size()){
		int u = q.front();
		q.pop();
		visSPFA[u] = false;
		for(int i=head[u]; i; i=edge[i].nextEdge){
			int v = edge[i].destination;
			if(dis[x][v] > dis[x][u]+1){
				dis[x][v] = dis[x][u]+1;
				if(!visSPFA[v]){
					visSPFA[v] = true;
					q.push(v);
				}
			}
		}
	}
}

double DFS(int x, int y){
	if(visDFS[x][y]) return f[x][y];
	visDFS[x][y] = true;
	if(x == y) return f[x][y] = 0;
	int u = nextStep[x][y], v = nextStep[u][y];
	if(u == y || v == y) return f[x][y] = 1;
	f[x][y] = 1;
	for(int i=head[y]; i; i=edge[i].nextEdge){
		int z = edge[i].destination;
		f[x][y] += DFS(v, z) / (degree[y]+1);
	}
	f[x][y] += DFS(v, y) / (degree[y] + 1);
	return f[x][y];
}

int main(){
	scanf("%d%d%d%d",&n,&e,&c,&m);
	for(int i=1;i<=e;i++){
		int u, v;
		scanf("%d%d",&u,&v);
		AddEdge(u, v); AddEdge(v, u);
	}
	for(int i=1;i<=n;i++)
		SPFA(i);
	memset(nextStep, 0x3f3f3f3f, sizeof(nextStep));
	for(int x=1;x<=n;x++)
		for(int i=head[x],y=edge[i].destination; i; i=edge[i].nextEdge,y=edge[i].destination)
			for(int z=1;z<=n;z++)
				if(dis[x][z] == 1+dis[y][z]) nextStep[x][z] = min(nextStep[x][z],y);
	printf("%.3lf",DFS(c, m));
}