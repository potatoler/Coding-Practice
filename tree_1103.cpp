#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, head[MaxN], cntEdge;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int depth, father, subtreeSize, heavySon, DFN, chainTop;
}vertex[MaxN];
struct SegmentTree{
	int l, r, ans, max, value;
	bool clear;
}tree[MaxN*4];
int idx[MaxN], stamp, cntDFN;
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
		vertex[thisSon].depth = vertex[x].depth + 1;
		vertex[thisSon].father = x;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
	return;
}

inline void DFS2(int x, int top){
	vertex[x].DFN = ++cntDFN;
	idx[cntDFN] = x;
	vertex[x].chainTop = top;
	if(vertex[x].heavySon) DFS2(vertex[x].heavySon, top);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
	return;
}

inline void Update(int x){
	tree[x].max = max(tree[x<<1].max, tree[x<<1|1].max);
	return;
}

inline void Calculate(int x){
	tree[x].ans = min(tree[x].value - 2*tree[x].max, min(tree[x<<1].ans, tree[x<<1|1].ans));
	return;
}

inline void Clear(int x){
	tree[x].value = tree[x].ans = INT_MAX;
	tree[x].clear = true;
	return;
}

inline void PassTag(int x){
	if(!tree[x].clear) return;
	Clear(x<<1);
	Clear(x<<1|1);
	tree[x].clear = false;
	return;
}

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	tree[x].value = tree[x].ans = INT_MAX;
	if(l == r){
		tree[x].max = vertex[idx[l]].depth;
		return;
	}
	int mid = (l+r) >> 1;
	Build(x<<1, l, mid);
	Build(x<<1|1, mid+1, r);
	Update(x);
}

inline void Change(int x, int ql, int qr, int w){
	if(qr < tree[x].l || tree[x].r < ql) return;
	if(ql <= tree[x].l && tree[x].r <= qr){
		tree[x].value = min(tree[x].value, w);
		tree[x].ans = min(tree[x].ans, tree[x].value - 2*tree[x].max);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	PassTag(x);
	Change(x<<1, ql, qr, w);
	Change(x<<1|1, ql, qr, w);
	Calculate(x);
}

inline int Ask(int x, int ql, int qr, int w){
	if(qr < tree[x].l || tree[x].r < ql) return INT_MAX;
	if(ql <= tree[x].l && tree[x].r <= qr) return min(tree[x].ans, w-2*tree[x].max);
	int mid = (tree[x].l + tree[x].r) >> 1;
	PassTag(x);
	w = min(w, tree[x].value);
	int res = INT_MAX;
	if(ql <= mid) res = min(res, Ask(x<<1, ql, qr, w));
	if(qr > mid) res = min(res, Ask(x<<1|1, ql, qr, w));
	return res;
}

inline void Modify(int x, int w){
	while(x){
		Change(1, vertex[xTop].DFN, vertex[x].DFN, w);
		x = vertex[xTop].father;
	}
	return;
}

inline int Query(int x){
	int res = INT_MAX;
	while(x){
		res = min(res, Ask(1, vertex[xTop].DFN, vertex[x].DFN, INT_MAX));
		x = vertex[xTop].father;
	}
	return res;
}

signed main(){
//	freopen("tree.in", "r", stdin);
//	freopen("tree.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v);
		AddEdge(v, u);
	}
	DFS1(1);
	DFS2(1,1);
	Build(1, 1, n);
	for(int i=1; i<=m; i++){
		int op = Read(), x = Read();
		if(op == 1) Modify(x, vertex[x].depth+i);
		else if(op == 2) Clear(1);
		else{
			if(Query(x) <= i-vertex[x].depth) printf("wrxcsd\n");
			else printf("orzFsYo\n");
		}
	}
	return 0;
}