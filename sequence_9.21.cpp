#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, k, maxAnd, maxOr, tmp, a[MaxN];
struct SegmentTree{
	int value, l, r;
}tree[MaxN * 4];

inline int Read(){
	int num  = 0, op = 1;
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
	if(l == r){
		tree[x].value = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	Build(x<<1, l, mid);
	Build(x<<1|1, mid+1, r);
	tree[x].value = tree[x<<1].value & tree[x<<1|1].value;
	return;
}

inline void Query(int x, int ql, int qr){
	if(tree[x].l == ql && tree[x].r == qr){
		tmp &= tree[x].value;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(qr <= mid) Query(x<<1, ql, qr);
	else if(ql > mid) Query(x<<1|1, ql, qr);
	else{
		Query(x<<1, ql, mid);
		Query(x<<1|1, mid+1, qr);
	}
	return;
}

signed main(){
//	freopen("sequence.in", "r", stdin);
//	freopen("sequence.out", "w", stdout);
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		maxOr |= a[i];
	}
	Build(1, 1, n);
	for(int i=1; i<=n-k+1; i++){
		tmp = (1<<31)-1;
		Query(1, i, i+k-1);
		maxAnd = max(maxAnd, tmp);
	}
	printf("%lld %lld", maxOr, maxAnd);
	return 0;
}