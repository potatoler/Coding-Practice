#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 300005;
int n, m, cntEdge, cntDFN, cntSeg, head[MaxN], serial[MaxN],ans[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int father, DFN, depth, subtreeSize, chainTop, heavySon, root, w;
}vertex[MaxN];
struct SegmentTree{
	int leftSon, rightSon, value;
}seg[MaxN * 25];

#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
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
}

inline void DFS2(int x, int top){
	vertex[x].DFN = ++cntDFN;
	serial[vertex[x].DFN] = x;
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
}

inline int LCA(int x, int y){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	return x;
}

inline void AddSeg(int &x, int l, int r, int pos, int val){
	if(!x) x = ++cntSeg;
	if(l == r){
		seg[x].value += val;
		return;
	}
	int mid = (l + r) / 2;
	if(pos <= mid) AddSeg(seg[x].leftSon, l, mid, pos, val);
	else AddSeg(seg[x].rightSon, mid+1, r, pos, val);
}

inline int Ask(int x, int l, int r, int pos){
	if(!x) return 0;
	if(l == r) return seg[x].value;
	int mid = (l + r) / 2;
	if(pos <= mid) return Ask(seg[x].leftSon, l, mid, pos);
	else return Ask(seg[x].rightSon, mid+1, r, pos);
}

inline int Merge(int a, int b, int l, int r){
	if(!a || !b) return a + b;
	if(l == r) seg[a].value += seg[b].value;
	else{
		int mid = (l + r) / 2;
		seg[a].leftSon = Merge(seg[a].leftSon, seg[b].leftSon, l, mid);
		seg[a].rightSon = Merge(seg[a].rightSon, seg[b].rightSon, mid+1, r);
	}
	return a;
}

inline void DFS(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		DFS(thisSon);
		vertex[x].root = Merge(vertex[x].root, vertex[thisSon].root, 1, n*2);
	}
	if(vertex[x].w && n+vertex[x].depth+vertex[x].w <= n*2) ans[x] += Ask(vertex[x].root, 1, n*2, n+vertex[x].depth+vertex[x].w);
	ans[x] += Ask(vertex[x].root, 1, n*2, n+vertex[x].depth-vertex[x].w);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		AddEdge(u, v);
		AddEdge(v, u);
	}
	DFS1(1);
	DFS2(1,1);
	for(int i=1;i<=n;i++)
		scanf("%d",&vertex[i].w);
	for(int i=1;i<=m;i++){
		int x, y, lca;
		scanf("%d%d",&x,&y);
		lca = LCA(x, y);
		AddSeg(vertex[x].root, 1, n*2, n+vertex[x].depth, 1);
		AddSeg(vertex[y].root, 1, n*2, n+vertex[lca].depth*2-vertex[x].depth, 1);
		AddSeg(vertex[lca].root, 1, n*2, n+vertex[x].depth, -1);
		AddSeg(vertex[vertex[lca].father].root, 1, n*2, n+vertex[lca].depth*2-vertex[x].depth, -1);
	}
	DFS(1);
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}