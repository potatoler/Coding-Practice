#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, W, H, ans, a[MaxN*2];
struct SegmentTree{
	int value, tag;
}tree[MaxN*2*4];

struct Node{
	int x, y1, y2, value;
	bool operator < (const Node &b) const{
		return x == b.x? value > b.value : x < b.x;
	}
}node[MaxN*2];

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

inline void PassTag(int x){
	if(!tree[x].tag) return;
	tree[x<<1].tag += tree[x].tag;
	tree[x<<1|1].tag += tree[x].tag;
	tree[x<<1].value += tree[x].tag;
	tree[x<<1|1].value += tree[x].tag;
	tree[x].tag = 0;
	return;
}

inline void Change(int x, int l, int r, int ql, int qr, int w){
	if(ql <= l && r <= qr){
		tree[x].tag += w;
		tree[x].value += w;
		return;
	}
	int mid = (l+r) >> 1;
	PassTag(x);
	if(ql <= mid) Change(x<<1, l, mid, ql, qr, w);
	if(qr > mid) Change(x<<1|1, mid+1, r, ql, qr, w);
	tree[x].value = max(tree[x<<1].value, tree[x<<1|1].value);
	return;
}

signed main(){
//	freopen("frame.in", "r", stdin);
//	freopen("frame.out", "w", stdout);
	n = Read(), W = Read(), H = Read();
	for(int i=1; i<=n; i++){
		int x = Read(), y = Read(), w = Read();
		node[i] = (Node){x, y, y+H-1, w};
		node[i+n] = (Node){x+W-1, y, y+H-1, -w};
		a[i] = y;
		a[i+n] = y+H-1;
	}
	n <<= 1;
	sort(a+1, a+1+n);
	int idx = unique(a+1, a+1+n) - a-1;
	sort(node+1, node+1+n);
//	printf("%lld\n", idx);
//	for(int i=1; i<=n; i++){
//		printf("%lld %lld %lld %lld\n", node[i].x, node[i].y1, node[i].y2, node[i].value);
//	}
	for(int i=1; i<=n; i++){
		int l = lower_bound(a+1, a+1+idx, node[i].y1) - a;
		int r = lower_bound(a+1, a+1+idx, node[i].y2) - a;
//		exit(0);
		Change(1, 1, idx, l, r, node[i].value);
		ans = max(ans, tree[1].value);
	}
	printf("%lld", ans);
	return 0;
}