#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, m, a, head[MaxN], belong[MaxN], cntEdge, ans, quest[MaxN];
bool visited[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int father, depth, heavySon, chainTop, subtreeSize;
}vertex[MaxN];
#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

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

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].father = x;
		vertex[thisSon].depth = vertex[x].depth + 1;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
	return;
}

inline void DFS2(int x, int top){
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
	return;
}

inline int LCA(int x, int y){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	return x;
}

inline int Find(int x){
	if(belong[x] == x) return x;
	else return belong[x] = Find(belong[x]);
}

inline void Update(int u, int v){
	if(vertex[u].depth < vertex[v].depth) return;
	visited[u] = true;
	belong[u] = vertex[u].father;
	Update(Find(vertex[u].father), v);
	return;
}

signed main(){
//	freopen("train.in", "r", stdin);
//	freopen("train.out", "w", stdout);
	n = Read(), m = Read(), a = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v);
		AddEdge(v,u);
	}
	for(int i=1; i<=n; i++){
		visited[i] = false;
		belong[i] = i;
	}
//	for(int i=1; i<=m; i++)
//		quest[i] = Read(), visited[i] = false;
	visited[a] = true;
	vertex[1].depth = 1;
	DFS1(1);
	DFS2(1, 1);
	for(int i=1; i<=m; i++){
		int b = Read();
		if(visited[b]) continue;
		int lca = LCA(a,b);
		ans += vertex[a].depth + vertex[b].depth - 2*vertex[lca].depth;
		Update(a, lca);
		Update(b, lca);
		a = b;
	}
//	for(int i=1; i<=n; i++)
//		printf("%lld %lld %lld\n", vertex[i].depth, vertex[i].heavySon, vertex[i].chainTop);
	printf("%lld", ans);
	return 0;
}