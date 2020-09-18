#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<set>
using namespace std;
const int MaxN = 50004, INF = 1e9;
int n, m, value[MaxN];
struct SegmentTree{
	int l, r;
	multiset<int> s;
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

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	tree[x].s.insert(INF), tree[x].s.insert(-INF);
	for(int i=l; i<=r; i++)
		tree[x].s.insert(value[i]);
	if(l == r) return;
	int mid = (l + r) >> 1;
	Build(x<<1, l, mid), Build(x<<1|1, mid+1, r);
}

inline void Change(int x, int pos, int w){
	tree[x].s.erase(tree[x].s.find(value[pos]));
	tree[x].s.insert(w);
	if(tree[x].l == tree[x].r) return;
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(pos <= mid) Change(x<<1, pos, w);
	else Change(x<<1|1, pos, w);
}

inline int Query(int x, int ql, int qr, int w){
	if(ql <= tree[x].l && tree[x].r <= qr){
		return *--tree[x].s.lower_bound(w);
//		auto res = tree[x].s.lower_bound(w);
//		res--;
//		return *res;
	}
	int mid = (tree[x].l + tree[x].r) >> 1, ans = -INF;
	if(ql <= mid) ans = max(ans, Query(x<<1, ql, qr, w));
	if(qr > mid) ans = max(ans, Query(x<<1|1, ql, qr, w));
	return ans;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		value[i] = Read();
	Build(1, 1, n);
	while(m--){
		int op = Read();
		if(op == 1){
			int p = Read(), x = Read();
			Change(1, p, x);
			value[p] = x;
		}
		else{
			int l = Read(), r = Read(), x = Read();
			printf("%d\n", Query(1, l, r, x));
		}
	}
	return 0;
}