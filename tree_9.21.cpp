#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006, Mod = 1000000007;
int n, q, head[MaxN], cntEdge;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int father[20], f, g, depth;
}vertex[MaxN];
#define thisSon edge[i].destination

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS1(int x, int father){
	vertex[x].father[0] = father;
	vertex[x].f = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		DFS1(thisSon, x);
		vertex[x].f = (vertex[x].f + vertex[thisSon].f + 1) % Mod;
	}
	vertex[x].f = (vertex[x].f + 1) % Mod;
	return;
}

inline void DFS2(int x, int father){
	int sum = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) sum = (sum + vertex[x].g + 1) % Mod;
		else sum = (sum + vertex[thisSon].f + 1) % Mod;
	}
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		vertex[thisSon].g = ((sum - vertex[thisSon].f) % Mod + Mod) % Mod;
		DFS2(thisSon, x);
	}
	return;
}

inline void DFS3(int x, int father){
	vertex[x].depth =  vertex[father].depth + 1;
	vertex[x].f = (vertex[x].f + vertex[father].f) % Mod;
	vertex[x].g = (vertex[x].g + vertex[father].g) % Mod;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		DFS3(thisSon, x);
	}
	return;
}

inline int LCA(int x, int y){
	if(vertex[x].depth < vertex[y].depth) swap(x,y);
	int d = vertex[x].depth - vertex[y].depth;
	if(d) for(int i=0; i<=log(n)/log(2)+1 && d; i++, d>>=1)
			if(d&1) x = vertex[x].father[i];
	if(x == y) return x;
	for(int i=log(n)/log(2)+1; i>=0; i--)
		if(vertex[x].father[i] != vertex[y].father[i]){
			x = vertex[x].father[i];
			y = vertex[y].father[i];
		}
	return vertex[x].father[0];
}

signed main(){
	n = Read(), q = Read();
	for(int i=1; i<=n-1; i++){
		int u = Read(), v = Read();
		AddEdge(u, v);
		AddEdge(v, u);
	}
	DFS1(1,-1);
	vertex[1].f = vertex[1].g = 0;
	DFS2(1,-1);
	DFS3(1,-1);
	for(int i=1; i<=log(n)/log(2)+1; i++)
		for(int j=1; j<=n; j++)
			vertex[j].father[i] = vertex[vertex[j].father[i-1]].father[i-1];
	for(int i=1; i<=q; i++){
		int u = Read(), v = Read();
		int lca = LCA(u,v), ans = (vertex[u].f - vertex[lca].f + vertex[v].g - vertex[lca].g + Mod) % Mod;
		printf("%lld\n", ans);
	}
	return 0;
}