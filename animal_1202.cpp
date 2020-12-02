#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 998244353, Inv = 828542813;
int n, head[MaxN], cntEdge, cntDFN, p[MaxN], ans[MaxN];
int q[MaxN], hd, tl;
int st[MaxN], tp;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int father, depth, heavySon, subtreeSize, chainTop, DFN;
}vertex[MaxN];
struct Segment{
	int l, r, value, tag;
};
#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop
class SegmentTree{
private:
	Segment tree[MaxN*4];
public:
	inline void Update(int x){
		tree[x].value = (tree[x<<1].value + tree[x<<1|1].value) % Mod;
	}
	
	inline void PassTag(int x){
		if(tree[x].tag == 1) return;
		tree[x<<1].value = tree[x<<1].value * tree[x].tag % Mod;
		tree[x<<1].tag = tree[x<<1].tag * tree[x].tag % Mod;
		tree[x<<1|1].value = tree[x<<1|1].value * tree[x].tag % Mod;
		tree[x<<1|1].tag = tree[x<<1|1].tag * tree[x].tag % Mod;
		tree[x].tag = 1;
		return;
	}
	
	inline void Build(int x, int l, int r){
		tree[x].l = l, tree[x].r = r;
		tree[x].value = tree[x].tag = 1;
		if(l == r) return;
		int mid = (tree[x].l + tree[x].r) >> 1;
		Build(x<<1, l, mid);
		Build(x<<1|1, mid+1, r);
		Update(x);
		return;
	}
	
	inline void Change(int x, int ql, int qr, int w){
		if(ql <= tree[x].l && tree[x].r <= qr){
			tree[x].value = tree[x].value * w % Mod;
			tree[x].tag = tree[x].tag * w % Mod;
			return;
		}
		PassTag(x);
		int mid = (tree[x].l + tree[x].r) >> 1;
		if(ql <= mid) Change(x<<1, ql, qr, w);
		if(qr > mid) Change(x<<1|1, ql, qr, w);
		Update(x);
		return;
	}
	
	inline int Query(int x, int ql, int qr){
		if(ql <= tree[x].l && tree[x].r <= qr) return tree[x].value;
		PassTag(x);
		int mid = (tree[x].l + tree[x].r) >> 1;
		if(ql > mid) return Query(x<<1|1, ql, qr);
		else if(qr <= mid) return Query(x<<1, ql, qr);
		else return (Query(x<<1, ql, qr) + Query(x<<1|1, ql, qr)) % Mod;
	}
}seg;

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
	return;
}

inline void Change(int x, int w){
	while(xTop != 1){
		seg.Change(1, vertex[xTop].DFN, vertex[x].DFN, w);
		x = vertex[xTop].father;
	}
	seg.Change(1, 1, vertex[x].DFN, w);
	return;
}

inline int Query(int x){
	int res = 0;
	while(xTop != 1){
		res = (res + seg.Query(1, vertex[xTop].DFN, vertex[x].DFN)) % Mod;
		x = vertex[xTop].father;
	}
	res = (res + seg.Query(1, 1, vertex[x].DFN)) % Mod;
	return res;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		p[i] = (100 - Read()) * Inv % Mod;
	for(int i=2; i<=n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v);
		AddEdge(v,u);
	}
	DFS1(1);
	DFS2(1,1);
	seg.Build(1,1,n);
	hd = 0, tl = 0, tp = 0;
	int last = 0;
	q[hd] = 1;
	while(tl <= hd){
		int x = q[tl++];
		if(vertex[x].depth > last){
			last++;
			while(tp){
				Change(st[tp], p[st[tp]]);
				tp--;
			}
		}
		ans[x] = Query(x);
		st[++tp] = x;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			if(thisSon == vertex[x].father) continue;
			q[++hd] = thisSon;
		}
	}
	for(int i=1; i<=n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}