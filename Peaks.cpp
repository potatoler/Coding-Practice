#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long 
using namespace std;
const int MaxN = 100005, MaxM = 500005;
int n, m, q, cntTree;
int father[MaxN], root[MaxN], ans[MaxM], head[MaxN], notinit[MaxN], inited[MaxN];
struct Edge{
	int from, to, value;
	inline bool operator < (const Edge &a) const{
		return value < a.value;
	}
}edge[MaxM];
struct Query{
	int v, x, k, ID;
	inline bool operator < (const Query &q) const{
		return x < q.x;
	}
}query[MaxM];
struct SegtmentTree{
	int sum, ls, rs, size;
}tree[MaxN * 20];

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

inline int Find(int x){
	if(father[x] == x) return x;
	return father[x] = Find(father[x]);
}

inline void Insert(int &x, int l, int r, int pos){
	if(!x) x = ++cntTree;
	if(l == r){
		tree[x].sum++;
		return;
	}
	int mid = (l + r) / 2;
	if(pos <= mid) Insert(tree[x].ls, l, mid, pos);
	else Insert(tree[x].rs, mid+1, r, pos);
	tree[x].sum = tree[tree[x].ls].sum + tree[tree[x].rs].sum;
	return;
}

inline int Merge(int x, int y, int l, int r){
	if(!x || !y) return x | y;
	if(l == r){
		tree[x].sum += tree[y].sum;
		return x;
	}
	int mid = (l + r) / 2;
	tree[x].ls = Merge(tree[x].ls, tree[y].ls, l, mid);
	tree[x].rs = Merge(tree[x].rs, tree[y].rs, mid+1, r);
	tree[x].sum = tree[tree[x].ls].sum + tree[tree[x].rs].sum;
	return x;
}

inline int Ask(int x, int l, int r, int k){
	if(l == r) return l;
	int mid = (l + r) / 2;
	if(tree[tree[x].rs].sum >= k) return Ask(tree[x].rs, mid+1, r, k);
	return Ask(tree[x].ls, l, mid, k-tree[tree[x].rs].sum);
}

signed main(){
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=n; i++){
		notinit[i] = Read();
		inited[i] = notinit[i];
		tree[i].size = 1;
	}
	sort(inited+1, inited+1+n);
	int size = unique(inited+1, inited+1+n) - inited - 1;
	for(int i=1; i<=n; i++){
		int val = lower_bound(inited+1, inited+1+size, notinit[i]) - inited;
		Insert(root[i], 1, size, val);
	}
//	for(int i=1; i<=size; i++)
//		printf("%lld ", inited[i]);

	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		edge[i] = (Edge){u,v,w};
	}
	sort(edge+1, edge+1+m);
	for(int i=1; i<=q; i++){
		int v = Read(), x = Read(), k = Read();
		query[i] = (Query){v,x,k,i};
	}
	sort(query+1, query+1+q);
	for(int i=1; i<=n; i++)
		father[i] = i;
	int p = 0, k, u, v;
	for(int i=1; i<=q; i++){
		int x = query[i].x;
		while(edge[p+1].value <= x && p < m){
			p++;
			u = edge[p].from, v = edge[p].to;
			u = Find(u), v = Find(v);
			if(u == v) continue;
			father[v] = u;
			tree[u].size += tree[v].size;
			root[u] = Merge(root[u], root[v], 1, size);
		}
		u = query[i].v, k = query[i].k;
		if(tree[Find(u)].size < k) ans[query[i].ID] = -1;
		else ans[query[i].ID] = inited[Ask(root[Find(u)], 1, size, k)];
//		printf("%lld %lld %lld %lld %lld\n",Ask(root[Find(u)], 1, size, k), ans[query[i].ID], u, v, k);
	}
	for(int i=1; i<=q; i++)
		printf("%lld\n", ans[i]);
	return 0;
}