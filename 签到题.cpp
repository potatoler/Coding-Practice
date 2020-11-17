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
int n, q, head[MaxN], cntEdge, cntDFN, a[MaxN], ans[MaxN];
int idx[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination
struct Vertex{
	int depth, father, chainTop, DFN, subtreeSize, heavySon, value;
}vertex[MaxN];
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop
struct SegmentTree{
	int l, r, val;
}tree[MaxN*4];

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
	idx[cntDFN] = x;
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].heavySon || thisSon == vertex[x].father) continue;
		DFS2(thisSon, thisSon);
	}
	return;
}

inline void Update(int x){
	tree[x].val = tree[x<<1].val + tree[x<<1|1].val;
}

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	if(l == r){
		tree[x].val = vertex[idx[l]].value;
		vertex[idx[l]].value = 0;
		return;
	}
	int mid = (l+r) >> 1;
	Build(x<<1, l, mid);
	Build(x<<1|1, mid+1, r);
	Update(x);
	return;
}

inline void Add(int x, int pos, int w){
	tree[x].val += w;
	if(tree[x].l == tree[x].r) return;
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(pos <= mid) Add(x<<1, pos, w);
	else Add(x<<1|1, pos, w);
	return;
}

inline int Ask(int x, int ql, int qr){
	if(ql <= tree[x].l && tree[x].r <= qr) return tree[x].val;
	int res = 0, mid = (tree[x].l + tree[x].r) >> 1;
	if(ql <= mid) res += Ask(x<<1, ql, qr);
	if(qr > mid) res += Ask(x<<1|1, ql, qr);
	return res;
}

inline void Query(int x, int y){
	int res = 0;
	int xx = x, yy = y;
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		res += Ask(1, vertex[xTop].DFN, vertex[x].DFN);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	res += Ask(1, vertex[x].DFN, vertex[y].DFN);
	if(xx == x || yy == x){
		if(x != xx) swap(xx,yy);
		xx = vertex[xx].father;
		x = vertex[x].father;
		res += Ask(1, vertex[x].DFN, vertex[x].DFN);
	}
//	printf("%lld ", res);
	if(x == n+1 || !x) printf("?\n");
	else printf("%lld\n", res - vertex[xx].value - vertex[yy].value + vertex[x].value + vertex[vertex[x].father].value);
	return;
}

signed main(){
	n = Read(), q = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	a[n+1] = INT_MAX;
	for(int i=1; i<=n; i++)
		vertex[i].value = Read();
	int stack[MaxN], top = 0;
	stack[++top] = n+1;
	for(int i=n; i; i--){
		while(a[stack[top]] <= a[i]) top--;
		AddEdge(stack[top], i);
		stack[++top] = i;
	}
	DFS1(n+1);
	DFS2(n+1, n+1);
//	for(int i=1; i<=n+1; i++)
//		printf("%lld %lld %lld %lld %lld %lld\n", vertex[i].value, vertex[i].heavySon, vertex[i].DFN, vertex[i].subtreeSize, vertex[i].depth, idx[i]);
	Build(1, 1, n+1);
	while(q--){
		int op = Read(), x = Read(), y = Read();
		if(op-1) Query(x,y);
		else{
			Add(1, vertex[x].DFN, y*2);
			vertex[x].value += y;
		}
	}
	return 0;
}