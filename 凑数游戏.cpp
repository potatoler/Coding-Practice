#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005, MaxA = 100000000000000;
int n, m, a[MaxN], cntTree, PST[MaxN];
struct SegmentTree{
	int sum, lSon, rSon;
}tree[MaxN*4*25];

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

inline void Update(int x){
	tree[x].sum = tree[tree[x].lSon].sum + tree[tree[x].rSon].sum;
	return;
}

inline int Change(int x, int l, int r, int pos, int val){
	int rt = ++cntTree;
	tree[rt] = tree[x];
	if(l == r){
		tree[rt].sum += val;
		return rt;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) tree[rt].lSon = Change(tree[x].lSon, l, mid, pos, val);
	else tree[rt].rSon = Change(tree[x].rSon, mid+1, r, pos, val);
	Update(rt);
	return rt;
}

inline int Query(int p, int q, int l, int r, int ql, int qr){
	if(l > qr || r < ql) return 0;
	if(ql <= l && r <= qr) return tree[q].sum - tree[p].sum;
	int mid = (l + r) >> 1;
	return Query(tree[p].lSon, tree[q].lSon, l, mid, ql, qr) + Query(tree[p].rSon, tree[q].rSon, mid+1, r, ql, qr);
}

inline int Ask(int l, int r){
	int maxa = 0, presum = 0;
	while(true){
		int tmp = Query(PST[l-1], PST[r], 1, MaxA, maxa+1, presum+1);
		if(!tmp) return presum+1;
		maxa = presum+1;
		presum += tmp;
	}
	return presum+1;
}

signed main(){
//	freopen("c.in", "r", stdin);
//	freopen("c.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		PST[i] = Change(PST[i-1], 1, MaxA, a[i], a[i]);
	}
	while(m--){
		int l = Read(), r = Read();
		int ans = Ask(l, r);
		printf("%lld\n", ans);
	}
	return 0;
}