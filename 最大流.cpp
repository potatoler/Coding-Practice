#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, head[MaxN], cntEdge, f[MaxN], g[MaxN];
bool leaf[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*2];

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

inline void DFS1(int x, int fa){
	for(int i=head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		leaf[x] = false;
		DFS1(y,x);
		if(leaf[y]) f[x] += edge[i].value;
		else f[x] += min(edge[i].value, f[y]);
	}
}

inline void DFS2(int x, int fa){
	for(int i=head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		if(g[x] == min(f[y], edge[i].value)) g[y] = f[y] + edge[i].value;
		else g[y] = f[y] + min(g[x] - min(f[y], edge[i].value), edge[i].value);
		DFS2(y, x);
	}
}

signed main(){
	n = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	memset(leaf, true, sizeof(leaf));
	DFS1(1,0);
	g[1] = f[1];
//	printf("%lld\n", f[1]);
	DFS2(1, 0);
	int ans = 0;
	for(int i=1; i<=n; i++)
		ans = max(ans, g[i]);
	printf("%lld", ans);
	return 0;
}