#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int MaxN = 200005;
int n, m, head[MaxN], cntEdge, cntDFN, ans[MaxN];
int idx[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination
struct Vertex{
	int depth, father, chainTop, DFN, subtreeSize, heavySon;
}vertex[MaxN];
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop
struct Bisinessman{
	int x, y, serial, lca;
}bis[MaxN];
inline bool cmp(Bisinessman a, Bisinessman b){
	return vertex[a.lca].depth < vertex[b.lca].depth;
}

class BinaryIndexedTree{
	private:
	int storage[MaxN];
	
	public:
	inline void Add(int x, int val){
		for(;x<=n; x+=lowbit(x))
			storage[x] += val;
	}
	
	inline int Ask(int x){
		int res = 0;
		for(;x; x-=lowbit(x))
			res += storage[x];
		return res;
	}
}pre, suf;

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
	vertex[x].DFN = ++cntDFN;
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].heavySon || thisSon == vertex[x].father) continue;
		DFS2(thisSon, thisSon);
	}
	idx[x] = cntDFN;
	return;
}

inline int LCA(int x, int y){
	while(xTop != yTop){
		if(vertex[xTop].depth <= vertex[yTop].depth) swap(x,y);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth >= vertex[y].depth) swap(x,y);
	return x;
}

inline int Calculate(int x, int y){
	int res = 0;
	while(xTop != yTop){
		if(vertex[xTop].depth <= vertex[yTop].depth) swap(x,y);
		res += suf.Ask(vertex[x].DFN) - suf.Ask(vertex[xTop].DFN-1);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth >= vertex[y].depth) swap(x,y);
	res += suf.Ask(vertex[y].DFN) - suf.Ask(vertex[x].DFN-1);
	return res;
}

signed main(){
//	freopen("business.in","r",stdin);
//	freopen("business.out","w",stdout);
	n = Read(), m = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v), AddEdge(v,u);
	}
	vertex[1].depth = 1;
	DFS1(1);
	DFS2(1,1);
	for(int i=1; i<=m; i++){
		bis[i].x = Read(), bis[i].y = Read();
		if(bis[i].x > bis[i].y) swap(bis[i].x, bis[i].y);
		bis[i].lca = LCA(bis[i].x, bis[i].y);
		bis[i].serial = i;
		suf.Add(vertex[bis[i].lca].DFN, 1);
	}
	sort(bis+1, bis+1+m, cmp);
	for(int i=1, j=1; i<=m; i++){
		while(vertex[bis[j].lca].depth < vertex[bis[i].lca].depth){
			pre.Add(vertex[bis[j].x].DFN, 1);
			pre.Add(vertex[bis[j].y].DFN, 1);
			j++;
		}
		ans[bis[i].serial] = pre.Ask(idx[bis[i].lca]) - pre.Ask(vertex[bis[i].lca].DFN-1);
//		printf("%lld %lld %lld %lld\n", pre.Ask(idx[bis[i].lca]), pre.Ask(vertex[bis[i].lca].DFN-1), pre.Ask(idx[bis[i].lca]) - pre.Ask(vertex[bis[i].lca].DFN-1), Calculate(bis[i].x, bis[i].y));
		ans[bis[i].serial] += Calculate(bis[i].x, bis[i].y);
	}
	for(int i=1; i<=m; i++)
		printf("%lld\n", ans[i]-1);
}