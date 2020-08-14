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
const int MaxN = 200005;
int n, q, a[MaxN];
double sink, cosk;
struct SegmentTree{
	double sin, cos;
	int tag;
}tree[MaxN * 4];

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

inline void Pushup(int x){
	tree[x].sin = tree[x*2].sin + tree[x*2+1].sin;
	tree[x].cos = tree[x*2].cos + tree[x*2+1].cos;
	return;
}

inline void Update(int x, double sinx, double cosx){
	double sina = tree[x].sin, cosa = tree[x].cos;
	tree[x].sin = sina * cosx + cosa * sinx;
	tree[x].cos = cosa * cosx - sina * sinx;
	return;
}

inline void PassTag(int x){
	if(!tree[x].tag) return;
	double sinx = sin(tree[x].tag), cosx = cos(tree[x].tag);
	Update(x*2, sinx, cosx);
	Update(x*2+1, sinx, cosx);
	tree[x*2].tag += tree[x].tag;
	tree[x*2+1].tag += tree[x].tag;
	tree[x].tag = 0;
	return;
} 

inline void Build(int x, int l, int r){
	if( l== r){
		tree[x].sin = sin(a[l]);
		tree[x].cos = cos(a[l]);
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	Pushup(x);
}

inline void Change(int ql, int qr, int x, int l, int r, int k){
	if(ql <= l && r <= qr){
		Update(x, sink, cosk);
		tree[x].tag += k;
		return;
	}
	PassTag(x);
	int mid = (l + r) / 2;
	if(ql <= mid) Change(ql, qr, x*2, l, mid, k);
	if(qr > mid) Change(ql, qr, x*2+1, mid+1, r, k);
	Pushup(x);
}

inline double Query(int ql, int qr, int x, int l, int r){
	if(ql <= l && r <= qr) return tree[x].sin;
	double res = 0;
	PassTag(x);
	int mid = (l + r) / 2;
	if(ql <= mid) res += Query(ql, qr, x*2, l, mid);
	if(qr > mid) res += Query(ql, qr, x*2+1, mid+1, r);
	return res;
}

signed main(){
	int op, l, r, k;
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	Build(1, 1, n);
	q = Read();
	while(q--){
		op = Read(), l = Read(), r = Read();
		if(op == 1){
			k = Read();
			sink = sin(k), cosk = cos(k);
			Change(l, r, 1, 1, n, k);
		}
		else printf("%.1lf\n", Query(l, r, 1, 1, n));
	}
	return 0;
}
