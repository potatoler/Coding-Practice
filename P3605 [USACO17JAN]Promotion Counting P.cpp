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
int n, p[MaxN], fa[MaxN], root[MaxN], cntTree, head[MaxN], cntEdge, ans[MaxN];
struct SegmentTree{
	int ls, rs, value, l, r;
}tree[MaxN * 35];
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];

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

inline void Update(int x){
	tree[x].value = tree[tree[x].ls].value + tree[tree[x].rs].value;
}

inline void Build(int &x, int l, int r, int w){
	x = ++cntTree;
	tree[x].l = l, tree[x].r = r;
	if(l == r){
		tree[x].value = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(w <= mid) Build(tree[x].ls, l, mid, w);
	else Build(tree[x].rs, mid+1, r, w);
	Update(x);
}

inline void Add(int x, int w){
	if(tree[x].l == tree[x].r){
		tree[x].value++;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(w <= mid) Add(tree[x].ls, w);
	else Add(tree[x].rs, w);
	Update(x);
}

inline int Merge(int x, int y){
	if(!x) return y;
	if(!y) return x;
	if(tree[x].l == tree[x].r){
		tree[x].value += tree[y].value;
		return x;
	}
	tree[x].ls = Merge(tree[x].ls, tree[y].ls);
	tree[x].rs = Merge(tree[x].rs, tree[y].rs);
	Update(x);
	return x;
}

inline int Ask(int x, int l, int r){
	if(!x) return 0;
	if(tree[x].l == l && tree[x].r == r) return tree[x].value;
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(l <= mid){
		if(r > mid) return Ask(tree[x].ls, l, mid) + Ask(tree[x].rs, mid+1, r);
		else return Ask(tree[x].ls, l, r);
	}
	return Ask(tree[x].rs, l, r);
}

inline void DFS(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		DFS(y);
		root[x] = Merge(root[x], root[y]);
	}
	ans[x] = Ask(root[x], p[x]+1, 1e9);
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		p[i] = Read();
		Build(root[i], 1, 1e9, p[i]);
	}
	for(int i=2; i<=n; i++){
		fa[i] = Read();
		AddEdge(fa[i], i);
	}
	DFS(1);
	for(int i=1; i<=n; i++)
		printf("%lld\n", ans[i]);
	return 0;
} 