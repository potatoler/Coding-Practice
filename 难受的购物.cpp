#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005, MaxQ = 300005, INF = 1000000000000000000;
int n, q, w[MaxN];
int serial[MaxQ], ans[MaxQ];
vector<int> question[MaxN];

struct SegmentTree{
	int l, r, val;
};

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

class Index{
	private:
	SegmentTree tree[MaxN*4];
	
	public:
	inline void Build(int x, int l, int r){
		tree[x].l = l, tree[x].r = r, tree[x].val = INF;
		if(l == r) return;
		int mid = (l+r) >> 1;
		Build(x<<1, l, mid);
		Build(x<<1|1, mid+1, r);
		return;
	}

	inline void Modify(int x, int ql, int qr, int v){
		if(ql <= tree[x].l && tree[x].r <= qr){
			tree[x].val = min(tree[x].val, v);
			return;
		}
		int mid = (tree[x].l + tree[x].r) >> 1;
		if(ql <= mid) Modify(x<<1, ql, qr, v);
		if(qr > mid) Modify(x<<1|1, ql, qr, v);
		return;
	}

	inline int Ask(int x, int pos){
		if(tree[x].l == tree[x].r) return tree[x].val;
		int mid = (tree[x].l + tree[x].r) >> 1;
		if(pos <= mid) return min(tree[x].val, Ask(x<<1,pos));
		else return min(tree[x].val, Ask(x<<1|1, pos));
	}
}idx;

class President{
	private:
	SegmentTree tree[MaxN*200];
	
	public:
	int root[MaxN], cnt;
	
	inline void Insert(int &x, int l, int r, int ql, int qr){
		int y = x;
		x = ++cnt;
		tree[x] = tree[y];
		tree[x].val = max(tree[x].val, qr);
		if(l == r) return;
		int mid = (l+r) >> 1;
		if(ql <= mid) Insert(tree[x].l, l, mid, ql, qr);
		else Insert(tree[x].r, mid+1, r, ql, qr);
		return;
	}
	
	inline int Query(int x, int l, int r, int ql, int qr){
		if(!x) return 0;
		if(ql <= l && r <= qr) return tree[x].val;
		int mid = (l+r) >> 1, res = 0;
		if(ql <= mid) res = max(res, Query(tree[x].l, l, mid, ql, qr));
		if(qr > mid) res = max(res, Query(tree[x].r, mid+1, r, ql, qr));
		return res;
	}
}pre;

inline void Solve(){
	idx.Build(1, 1, n);
	for(int i=1; i<=n; i++){
		int x = w[i], pos = pre.Query(pre.root[i-1], 0, INF, 0, x);
		while(pos){
			idx.Modify(1, 1, pos, x-w[pos]);
			pos = pre.Query(pre.root[pos-1], 0, INF, (x+w[pos])/2+1, x);
		}
		for(int j=0; j<question[i].size(); j++)
			ans[question[i][j]] = min(ans[question[i][j]], idx.Ask(1, serial[question[i][j]]));
	}
	return;
}

signed main(){
//	freopen("shopping.in", "r", stdin);
//	freopen("shopping.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++)
		w[i] = Read();
	for(int i=1; i<=n; i++){
		pre.root[i] = pre.root[i-1];
		pre.Insert(pre.root[i], 0, INF, w[i], i);
	}
	q = Read();
	for(int i=1; i<=q; i++){
		int l = Read(), r = Read();
		question[r].push_back(i);
		serial[i] = l;
		ans[i] = INF;
	}
	Solve();
	for(int i=1; i<=n; i++)
		w[i] = INF - w[i];
	pre.cnt = 0;
	for(int i=1; i<=n; i++){
		pre.root[i] = pre.root[i-1];
		pre.Insert(pre.root[i], 0, INF, w[i], i);
	}
	Solve();
	for(int i=1; i<=q; i++)
		printf("%lld\n", ans[i]);
	return 0;
}