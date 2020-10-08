#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, q, cntEdge, head[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int father, chainTop, depth, heavySon, subtreeSize;
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
	if(vertex[x].heavySon) DFS2(vertex[x].heavySon, top);
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

signed main(){
	n = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v), AddEdge(v,u);
	}
	DFS1(1);
	DFS2(1,1);
	q = Read();
//	printf("%lld\n", LCA(4,5));
	while(q--){
		int a = Read(), b = Read(), c = Read(), d = Read();
		int lca_ab = LCA(a,b), lca_cd = LCA(c,d);
		if(LCA(a,c) == c && LCA(c,lca_ab) == lca_ab || LCA(a,d) == d && LCA(d,lca_ab) == lca_ab) printf("YES\n");
		else if(LCA(b,c) == c && LCA(c,lca_ab) == lca_ab || LCA(b,d) == d && LCA(d,lca_ab) == lca_ab) printf("YES\n");
		else if(LCA(b,lca_cd) == lca_cd && LCA(lca_ab,lca_cd) == lca_ab || LCA(a,lca_cd) == lca_cd && LCA(lca_ab,lca_cd) == lca_ab) printf("YES\n");
		else if(LCA(c,lca_ab) == lca_ab && LCA(lca_ab,lca_cd) == lca_cd || LCA(d,lca_ab) == lca_ab && LCA(lca_ab,lca_cd) == lca_cd) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}