#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, m, a[MaxN], difference[MaxN];
struct SgementTree{
	int l, r, sum, GCD;
}tree[MaxN * 4];

inline int Read(){
	int num = 0, op = 1;
	char ch  = getchar();
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

inline int GCD(int x, int y){
	return y? GCD(y, x%y) : x;
}

inline void Update(int x){
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	tree[x].GCD = GCD(tree[x*2].GCD, tree[x*2+1].GCD);
}

inline void Build(int x, int l, int r){
	tree[x].l = l, tree[x].r = r;
	if(l == r){
		tree[x].sum = tree[x].GCD = difference[l];
		return;
	}
	int mid = (l+r) >> 1;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	Update(x);
}

inline void Plus(int x, int pos, int value){
	if(tree[x].l == tree[x].r){
		tree[x].GCD += value;
		tree[x].sum += value;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(pos <= mid) Plus(x*2, pos, value);
	else Plus(x*2+1, pos, value);
	Update(x);
}

inline int SingelAsk(int x, int ql, int qr){
	if(ql <= tree[x].l && tree[x].r <= qr) return tree[x].sum;
	int mid = (tree[x].l + tree[x].r) >> 1;
	int ans = 0;
	if(ql <= mid) ans += SingelAsk(x*2, ql, qr);
	if(qr > mid) ans += SingelAsk(x*2+1, ql, qr);
	return ans;
}

inline int GCDAsk(int x, int ql, int qr){
	if(ql <= tree[x].l && tree[x].r <= qr) return tree[x].GCD;
	int mid = (tree[x].l + tree[x].r) >> 1;
	int lGCD = 0, rGCD = 0;
	if(ql <= mid) lGCD = GCDAsk(x*2, ql, qr);
	if(qr > mid) rGCD = GCDAsk(x*2+1, ql, qr);
	return GCD(lGCD, rGCD);
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		difference[i] = a[i] - a[i-1];
	}
	Build(1,1,n);
	char op[3]; int l, r, d;
	while(m--){
		scanf("%s", op);
		if(op[0] == 'C'){
			l = Read(), r = Read(), d = Read();
			Plus(1, l, d);
			if(r < n) Plus(1, r+1, -d);
		}
		else{
			l = Read(), r = Read();
			int Al = SingelAsk(1, 1, l);
			int ans = abs(GCD(Al, GCDAsk(1, l+1, r)));
			printf("%lld\n", ans);
		}
	}
	return 0;
}