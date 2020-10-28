#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 1000000007;
int n, q, cnt, DFN[MaxN], idx[MaxN];

struct Splay{
	int value, son[2], father, start, end, sum;
}splay[MaxN];

inline void DFS(int x){
	splay[x].start = cnt+1;
	if(splay[x].son[0]) DFS(splay[x].son[0]);
	DFN[x] = ++cnt;
	idx[cnt] = x;
	if(splay[x].son[1]) DFS(splay[x].son[1]);
	splay[x].end = cnt;
	splay[x].sum = (splay[splay[x].son[0]].sum + splay[splay[x].son[1]].sum + splay[x].value) % Mod;
	return;
}

inline int Identify(int x){
	return splay[splay[x].father].son[1] == x;
}

inline void NewRange(int x){
	splay[x].start = splay[x].son[0]? splay[splay[x].son[0]].start : DFN[x];
	splay[x].end = splay[x].son[1]? splay[splay[x].son[1]].end : DFN[x];
	return;
}

struct SegmentTree{
	int l, r, mul;
}tree[MaxN*4];

inline void Update(int x){
	tree[x].mul = tree[x<<1].mul * tree[x<<1|1].mul % Mod;
	return;
}

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	if(l == r){
		tree[x].mul = splay[idx[l]].sum;
		return;
	}
	int mid = (l+r) >> 1;
	Build(x<<1, l, mid);
	Build(x<<1|1, mid+1, r);
	Update(x);
	return;
}

inline void Change(int x, int pos, int w){
	if(tree[x].l == tree[x].r){
		tree[x].mul = w;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(pos <= mid) Change(x<<1, pos, w);
	else Change(x<<1|1, pos, w);
	Update(x);
	return;
}

inline int Query(int x, int ql, int qr){
	if(ql <= tree[x].l && tree[x].r <= qr) return tree[x].mul;
	int mid = (tree[x].l + tree[x].r) >> 1, res = 1;
	if(ql <= mid) res = res * Query(x<<1, ql, qr) % Mod;
	if(qr > mid) res = res * Query(x<<1|1, ql, qr) % Mod;
	return res;
}

inline void Rotate(int x){
	int y = splay[x].father, z = splay[y].father;
	int k = Identify(x);
	splay[y].son[k] = splay[x].son[k^1];
	splay[splay[x].son[k^1]].father = y;
	if(z){
		splay[z].son[Identify(y)] = x;
		splay[x].father = z;
	}
	splay[x].son[k^1] = y;
	splay[y].father = x;
	splay[x].sum = splay[y].sum;
	splay[y].sum = (splay[splay[y].son[1]].sum + splay[splay[y].son[0]].sum + splay[y].value) % Mod;
	NewRange(x), NewRange(y);
	Change(1, DFN[x], splay[x].sum);
	Change(1, DFN[y], splay[y].sum);
}

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

signed main(){
	freopen("splay.in", "r", stdin);
	freopen("splay.out", "w", stdout);
	n = Read(), q = Read();
	for(int i=1; i<=n; i++){
		splay[i].value = Read(), splay[i].son[0] = Read(), splay[i].son[1] = Read();
		if(splay[i].son[0]) splay[splay[i].son[0]].father = i;
		if(splay[i].son[1]) splay[splay[i].son[1]].father = i;
	}
	DFS(1);
	Build(1, 1, n);
	while(q--){
		int op = Read(), x = Read();
		if(op == 2) printf("%lld\n", Query(1, splay[x].start, splay[x].end));
		else{
			x = splay[x].son[op];
			if(x) Rotate(x);
		}
	}
	return 0;
}