#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
//#define int long long
using namespace std;
const int MaxN = 80001;
int n, m, t, q, cntEdge;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 4];
struct SegmentTree{
	int size, ls, rs;
}tree[MaxN * 600];
int value[MaxN], father[MaxN], son[MaxN], head[MaxN], root[MaxN], cntTree;
int cur[MaxN], size;
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
	return op * num;
}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void Build(int &x, int l, int r){
	x = ++cntTree;
	tree[x].size = 0;
	if(l == r) return;
	int mid = (l + r) / 2;
	Build(tree[x].ls, l, mid);
	Build(tree[x].rs, mid+1, r);
	return;
}

inline void Insert(int &x, int pre, int l, int r, int pos){
	x = ++cntTree;
	tree[x] = tree[pre];
	tree[x].size++;
	if(l == r) return;
	int mid = (l + r) / 2;
	if(pos <= mid) Insert(tree[x].ls, tree[pre].ls, l, mid, pos);
	else Insert(tree[x].rs, tree[pre].rs, mid+1, r, pos);
	return;
}

inline int Query(int x, int y, int pre1, int pre2, int l, int r, int k){
	if(l == r) return cur[l];
	int lsize = tree[tree[x].ls].size + tree[tree[y].ls].size - tree[tree[pre1].ls].size - tree[tree[pre2].ls].size;
	int mid = (l + r) / 2;
	if(k <= lsize) return Query(tree[x].ls, tree[y].ls, tree[pre1].ls, tree[pre2].ls, l, mid, k);
	else return Query(tree[x].rs, tree[y].rs, tree[pre1].rs, tree[pre2].rs, mid+1, r, k-lsize);
}

inline int Init(int x){
	return lower_bound(cur+1, cur+1+size, x) - cur;
}

inline int Find(int x){
	return father[x] == x? x : father[x] = Find(father[x]);
}

int st[MaxN][17], depth[MaxN];
bool visited[MaxN];

inline void DFS(int x, int fa, int rt){
	st[x][0] = fa;
	for(int k=1; k<=16; k++)
		st[x][k] = st[st[x][k-1]][k-1];
	son[rt]++;
	depth[x] = depth[fa] + 1;
	visited[x] = true;
	father[x] = fa;
	Insert(root[x], root[fa], 1, size, Init(value[x]));
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		if(v == fa) continue;
		DFS(v, x, rt);
	}
}

inline int LCA(int x, int y){
	if(x == y) return x;
	if(depth[x] > depth[y]) swap(x, y);
	for(int k=16; k>=0; k--)
		if(depth[st[y][k]] >= depth[x]) y = st[y][k];
	if(x == y) return x;
	for(int k=16; k>=0; k--)
		if(st[x][k] != st[y][k]){
			x = st[x][k];
			y = st[y][k];
		}
	return st[x][0];
}

inline void Reset(){
	memset(head,0,sizeof(head));
	memset(depth,0,sizeof(depth));
	memset(visited,0,sizeof(visited));
	memset(st,0,sizeof(st));
	memset(son,0,sizeof(son));
	cntEdge = cntTree = 0;
}

signed main(){
	t = Read();
	Reset();
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=n; i++){
		value[i] = Read();
		cur[i] = value[i];
		father[i] = i;
	}
	sort(cur+1, cur+1+n);
	size = unique(cur+1, cur+1+n) - cur - 1;
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(u, v);
		AddEdge(v, u);
	}
	Build(root[0], 1, size);
	for(int i=1; i<=n; i++)
		if(!visited[i]){
			DFS(i, 0, i);
			father[i] = i;
		}
	int lastans = 0;
	for(int i=1; i<=q; i++){
		char ch[3];
		int x, y, k;
		scanf("%s", ch);
		x = Read() ^ lastans;
		y = Read() ^ lastans;
		if(ch[0] == 'Q'){
			k = Read() ^ lastans;
			int lca = LCA(x,y);
			lastans = Query(root[x], root[y], root[lca], root[st[lca][0]], 1, size, k);
			printf("%lld\n", lastans);
		}
		else{
			AddEdge(x,y), AddEdge(y,x);
			int u = Find(x), v = Find(y);
			if(son[u] < son[y]) swap(u,v), swap(x,y);
			DFS(y, x, u);
		}
	}
	return 0;
} 