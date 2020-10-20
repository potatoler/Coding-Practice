#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 998244353;
int n, a[MaxN*2], cnt, ans = 1;
struct Segment{
	int l, r;
	bool operator < (const Segment &b) const{
		if(l == b.l) return r < b.r;
		else return l < b.l;
	}
}seg[MaxN];
struct SegmentTree{
	int l, r, add, sum, mul;
}tree[MaxN*8];
#define thisTree tree[x]
#define leftySon tree[x<<1]
#define rightSon tree[x<<1|1]

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
	thisTree.sum = (leftySon.sum + rightSon.sum) % Mod;
	return;
}

inline void PassTag(int x){
	if(thisTree.add == 0 && thisTree.mul == 1) return;
	leftySon.sum = (leftySon.sum * thisTree.mul + thisTree.add * (leftySon.r - leftySon.l + 1)) % Mod;
	rightSon.sum = (rightSon.sum * thisTree.mul + thisTree.add * (rightSon.r - rightSon.l + 1)) % Mod;
	leftySon.mul = leftySon.mul * thisTree.mul % Mod;
	rightSon.mul = rightSon.mul * thisTree.mul % Mod;
	leftySon.add = (leftySon.add * thisTree.mul + thisTree.add) % Mod;
	rightSon.add = (rightSon.add * thisTree.mul + thisTree.add) % Mod;
	thisTree.add = 0;
	thisTree.mul = 1;
	return;
}

inline void Build(int x, int l, int r){
	thisTree.l = l, thisTree.r = r;
	thisTree.add = 0, thisTree.mul = 1;
	if(l == r) return;
	int mid = (thisTree.l + thisTree.r) >> 1;
	Build(x<<1, l, mid), Build(x<<1|1, mid+1, r);
	Update(x);
	return;
}

inline void Multiplication(int x, int ql, int qr, int w){
	if(ql > qr) return;
	if(ql <= thisTree.l && thisTree.r <= qr){
		thisTree.add = thisTree.add * w % Mod;
		thisTree.mul = thisTree.mul * w % Mod;
		thisTree.sum = thisTree.sum * w % Mod;
		return;
	}
	PassTag(x);
	int mid = (thisTree.l + thisTree.r) >> 1;
	if(ql <= mid) Multiplication(x<<1, ql, qr, w);
	if(qr > mid) Multiplication(x<<1|1, ql, qr, w);
	Update(x);
	return;
}

inline void Add(int x, int ql, int qr, int w){
	if(ql > qr) return;
	if(ql <= thisTree.l && thisTree.r <= qr){
		thisTree.add = (thisTree.add + w) % Mod;
		thisTree.sum = (thisTree.sum + w * (thisTree.r - thisTree.l + 1)) % Mod;
		return;
	}
	PassTag(x);
	int mid = (thisTree.l + thisTree.r) >> 1;
	if(ql <= mid) Add(x<<1, ql, qr, w);
	if(qr > mid) Add(x<<1|1, ql, qr, w);
	Update(x);
	return;
}

inline int Query(int x, int ql, int qr){
	if(ql > qr) return 0;
	if(ql <= thisTree.l && thisTree.r <= qr) return thisTree.sum;
	PassTag(x);
	int res = 0, mid = (thisTree.l + thisTree.r) >> 1;
	if(ql <= mid) res += Query(x<<1, ql, qr);
	if(qr > mid) res += Query(x<<1|1, ql, qr);
	return res % Mod;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		int l = Read(), r = Read();
		seg[i] = (Segment){l,r};
		a[cnt++] = l, a[cnt++] = r;
	}
	sort(seg+1, seg+1+n);
	sort(a, a+cnt);
	cnt = unique(a, a+cnt)-a;
	for(int i=1; i<=n; i++){
		seg[i].l = lower_bound(a, a+cnt, seg[i].l) - a + 1;
		seg[i].r = lower_bound(a, a+cnt, seg[i].r) - a + 1;
	}
	Build(1, 1, cnt);
	int last = 0, p = 1;
	while(p <= n){
		int L = seg[last+1].l, R = seg[last+1].r;
		while(p<n && seg[p+1].l <= R){
			p++;
			R = max(R, seg[p].r);
		}
		Add(1, seg[last+1].r, seg[last+1].r, 1);
		for(int i = last+2; i<=p; i++){
			int sum = Query(1, seg[i].l, seg[i].r);
//			printf("%lld\n", sum);
			Add(1, seg[i].r, seg[i].r, sum);
			Multiplication(1, seg[i].r+1, R, 2);
			if(seg[i].l == L) Add(1, seg[i].r, seg[i].r, 1);
		}
		ans = ans * Query(1, R, R) % Mod;
		last = p++;
	}
	printf("%lld", ans);
	return 0;
}