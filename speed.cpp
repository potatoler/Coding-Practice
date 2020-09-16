#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 70004;
int n, m, head[MaxN], indx[MaxN*20], cntEdge, cntVedge, cntDFN, cntOp;

struct Vertex{
	int father, DFN, heavySon, chainTop, subtreeSize, depth;
}vertex[MaxN];

struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];

struct ValuedEdge{
	int x, y, nextEdge;
}vedge[MaxN * 20];

struct Operation{
	int type, x, y;
	Operation(){}
	Operation(int type_, int x_, int y_){
		type = type_;
		x = x_;
		y = y_;
	}
}operation[MaxN * 4];

int fa[MaxN], dep[MaxN], a[MaxN], b[MaxN], res[MaxN];

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

inline void AddValuedEdge(int p, int u, int v){
	cntVedge++;
	vedge[cntVedge].x = u;
	vedge[cntVedge].y = v;
	vedge[cntVedge].nextEdge = indx[p];
	indx[p] = cntVedge;
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
}

inline void DFS2(int x, int top){
	vertex[x].DFN = ++cntDFN;
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

inline int Distance(int x, int y){
	return vertex[x].depth + vertex[y].depth - 2*vertex[LCA(x,y)].depth;
}

inline int GetFather(int x){
	return fa[x] == x? x:GetFather(fa[x]);
}

inline void Merge(int x, int y, int &ans){
	x = GetFather(x), y = GetFather(y);
	// printf("%lld %lld\n%lld %lld %lld %lld\n", x, y, a[x], a[y], b[x], b[y]);
	int u, v, w=-1;
	if(Distance(a[x], a[y]) > w){
		w = Distance(a[x], a[y]);
		u = a[x], v = a[y];
	}
	// printf("%lld ", w);
	if(Distance(a[x], b[x]) > w){
		w = Distance(a[x],b[x]);
		u = a[x], v = b[x];
	}
	// printf("%lld ", w);
	if(Distance(a[x], b[y]) > w){
		w = Distance(a[x], b[y]);
		u = a[x], v = b[y];
	}
	// printf("%lld ", w);
	if(Distance(b[x], b[y]) > w){
		w = Distance(b[x], b[y]);
		u = b[x], v = b[y];
	}
	// printf("%lld ", w);
	if(Distance(b[x], a[y]) > w){
		w = Distance(b[x], a[y]);
		u = b[x], v = a[y];
	}
	// printf("%lld ", w);
	if(Distance(a[y], b[y]) > w){
		w = Distance(a[y], b[y]);
		u = a[y], v = b[y];
	}
	// printf("%lld\n", w);
	if(ans < w) ans = w;
	if(dep[x] == dep[y]){
		dep[x]++;
		operation[++cntOp] = Operation(0,x,0);
	}
	else if(dep[x] < dep[y]) swap(x,y);
	operation[++cntOp] = Operation(1,y,0);
	operation[++cntOp] = Operation(2,x,a[x]);
	operation[++cntOp] = Operation(3,x,b[x]);
	fa[y] = x;
	a[x] = u;
	b[x] = v;
	// printf("%lld %lld %lld\n", x, u, v);
	// printf("%lld\n", ans);
}

inline void Reset(int x){
	// printf("\n%lld\n", cntOp);
	while(cntOp > x){
		if(!operation[cntOp].type) dep[operation[cntOp].x]--;
		if(operation[cntOp].type == 1) fa[operation[cntOp].x] = operation[cntOp].x;
		if(operation[cntOp].type == 2) a[operation[cntOp].x] = operation[cntOp].y;
		if(operation[cntOp].type == 3) b[operation[cntOp].x] = operation[cntOp].y;
		cntOp--;
		// printf("%lld %lld %lld %lld\n", dep[operation[cntOp].x], fa[operation[cntOp].x], a[operation[cntOp].x], b[operation[cntOp].x]);
	}
	// printf("\n");
}

inline void Add(int x, int l, int r, int al, int ar, int u, int v){
	if(al <= l && r <= ar){
		AddValuedEdge(x,u,v);
		return;
	}
	int mid = (l + r) >> 1;
	if(al<=mid) Add(x*2, l, mid, al, ar, u, v);
	if(ar>mid) Add(x*2+1, mid+1, r, al, ar, u, v);
}

inline void Solve(int x, int l, int r, int ans){
	int pos = cntOp;
	for(int i = indx[x]; i; i = vedge[i].nextEdge)
		Merge(vedge[i].x, vedge[i].y, ans);
	if(l == r){
		res[l] = ans;
		Reset(pos);
		return;
	}
	int mid = (l + r) >> 1;
	Solve(x*2, l, mid, ans);
	Solve(x*2+1, mid+1, r, ans);
	Reset(pos);
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<n; i++){
		int x = Read(), y = Read(), l = Read(), r = Read();
		AddEdge(x,y), AddEdge(y,x);
		Add(1,1,n,l,r,x,y);
	}
	DFS1(1);
	DFS2(1,1);
	// for(int i=1; i<=n; i++)
	// 	printf("%lld %lld %lld %lld %lld\n", vertex[i].subtreeSize, vertex[i].depth, vertex[i].heavySon, vertex[i].chainTop, vertex[i].DFN);
	// for(int i=1; i<=cntVedge; i++)
	// 	printf("%lld %lld %lld\n", vedge[i].destination, vedge[i].value, vedge[i].nextEdge);
	for(int i=1; i<=n; i++)
		fa[i] = a[i] = b[i] = i;
	Solve(1,1,n,0);
	while(m--){
		int x = Read();
		printf("%lld\n", res[x]);
	}
	return 0;
}