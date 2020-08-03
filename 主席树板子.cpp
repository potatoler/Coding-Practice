#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 200005;
struct SegmentTree{
	int lSon, rSon, value;
}seg[MaxN<<5];
int root[MaxN];
int n, m, a[MaxN], f[MaxN], cnt, len;

inline int Build(int l, int r){
	int x = ++cnt;
	seg[x].value = 0;
	if(l == r) return x;
	int mid = (l + r) / 2;
	seg[x].lSon = Build(l, mid);
	seg[x].rSon = Build(mid+1, r);
	return x;
}

inline int Update(int k, int l, int r, int x){
	int y = ++cnt;
	seg[y].lSon = seg[x].lSon;
	seg[y].rSon = seg[x].rSon;
	seg[y].value = seg[x].value + 1;
	if(l == r) return y;
	int mid = (l + r) / 2;
	if(k <= mid) seg[y].lSon = Update(k, l, mid, seg[y].lSon);
	else seg[y].rSon = Update(k, mid+1, r, seg[y].rSon);
	return y;
}

inline int Query(int u, int v, int l, int r, int k){
	int mid = (l + r) / 2;
	int val = seg[seg[v].lSon].value - seg[seg[u].lSon].value;
	if(l == r) return l;
	if(k <= val) return Query(seg[u].lSon, seg[v].lSon, l, mid, k);
	else return Query(seg[u].rSon, seg[v].rSon, mid+1, r, k-val);
}

inline int get(const int &val){
	return lower_bound(f+1, f+len+1, val) - f;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",
		&a[i]);
	memcpy(f, a, sizeof(f));
	sort(f+1, f+1+n);
	len = unique(f+1, f+1+n) - f - 1;
	root[0] = Build(1, len);
	for(int i=1;i<=n;i++)
		root[i] = Update(get(a[i]), 1, len, root[i-1]);
	int l, r, k;
	while(m--){
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n", f[Query(root[l-1], root[r], 1, len, k)]);
	}
	return 0;
}