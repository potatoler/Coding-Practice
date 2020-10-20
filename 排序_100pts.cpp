#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#include<utility>
#include<map>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, m, ans, a[MaxN], idx[MaxN], bit[MaxN], cnt[MaxN];
map<int, int> mp;
struct SegmentTree{
	int l, r, value, serial;
	bool operator < (const SegmentTree &y) const{
		return value < y.value;
	}
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
	if(l == r) return;
	int mid = (l + r) >> 1;
	Build(x<<1, l, mid), Build(x<<1|1, mid+1, r);
	return;
}

inline SegmentTree Query(int x, int ql, int qr){
	if(ql == tree[x].l && tree[x].r == qr) return tree[x];
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(ql > mid) return Query(x<<1|1, ql, qr);
	else{
		if(qr <= mid) return Query(x<<1, ql, qr);
		else return min(Query(x<<1, ql, mid), Query(x<<1|1, mid+1, qr));
	}
}

inline void Change(int x, int pos, SegmentTree w){
	if(tree[x].l == tree[x].r){
		w.l = tree[x].l, w.r = tree[x].r;
		tree[x] = w;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(pos <= mid) Change(x<<1, pos, w);
	else Change(x<<1|1, pos, w);
	int tmpl = tree[x].l, tmpr = tree[x].r;
	tree[x] = min(tree[x<<1], tree[x<<1|1]);
	tree[x].l = tmpl, tree[x].r = tmpr;
	return;
}

inline void Insert(int x){
	while(x <= 500000){
		bit[x]++;
		x += x&-x;
	}
	return;
}

inline int Search(int x){
	int res = 0;
	while(x){
		res += bit[x];
		x -= x&-x;
	}
	return res;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		idx[i] = a[i];
	}
	int tmp = 0;
	sort(idx+1, idx+1+n);
	for(int i=1; i<=n; i++)
		if(i == 1 || idx[i] != idx[i-1]) mp[idx[i]] = ++tmp;
	for(int i=1; i<=n; i++)
		a[i] = mp[a[i]];
	Build(1, 1, n);
	for(int i=n; i>=1; i--){
		cnt[i] = Search(a[i]-1);
		ans += cnt[i];
		Insert(a[i]);
		SegmentTree w = (SegmentTree){0,0,a[i],i};
		Change(1, i, w);
	}
	while(m--){
		int pos = Read();
		while(true){
			SegmentTree cur = Query(1, pos, n);
			if(cur.value > a[pos]) break;
			ans -= cnt[cur.serial];
			SegmentTree w = (SegmentTree){0,0,LLONG_MAX,LLONG_MAX};
			Change(1, cur.serial, w);
		}
		printf("%lld\n", ans);
	}
	return 0;
}