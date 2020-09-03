#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, t, head[MaxN], cntEdge, father[MaxN][25], depth[MaxN], ans[MaxN], dist[MaxN], f[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN * 2];

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void Build(int x, int fa){
	father[x][0] = fa;
	depth[x] = depth[fa] + 1;
	for(int i=1; i<25; i++)
		father[x][i] = father[father[x][i-1]][i-1];
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int thisSon = edge[i].destination;
		if(thisSon == fa) continue;
		dist[thisSon] = dist[x] + edge[i].value;
		Build(thisSon, x);
	}
	return;
}

inline int far(int x){
	int k = x;
	for(int i=24; i>=0; i--)
		if(dist[x] - dist[father[k][i]] <= t) k = father[k][i];
	return k;
}

inline void Query(int x, int fa){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int thisSon = edge[i].destination;
		if(thisSon == fa) continue;
		Query(thisSon, x);
		ans[x] += ans[thisSon];
	}
	ans[x] += f[x];
	return;
}

signed main(){
	n = Read(), t = Read();
	for(int i=2; i<=n; i++){
		int fa = Read(), w = Read();
		AddEdge(fa,i,w), AddEdge(i,fa,w);
	}
	Build(1,0);
	dist[0] = -INT_MAX;
	for(int i=1; i<=n; i++){
		int k = far(i);
		f[i]++;
		f[father[k][0]]--;
	}
	Query(1,0);
	for(int i=1; i<=n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}