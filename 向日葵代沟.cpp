#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m;
bool visited[MaxN];
struct SegmentTree{
	int l, r, value[2];
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
	tree[x].value[0] = 0, tree[x].value[1] = n+1;
	if(l == r) return;
	int mid = (l+r) >> 1;
	Build(x*2, l, mid), Build(x*2+1, mid+1, r);
	return;
}

inline void PassTag(int x, int dir){
	if(!tree[x].value[dir]) return;
	tree[x*2].value[dir] = tree[x].value[dir];
	tree[x*2+1].value[dir] = tree[x].value[dir];
	tree[x].value[dir] = 0;
	return;
}

inline void Change(int x, int cl, int cr, int dir, int w){
	if(cl <= tree[x].l && tree[x].r <= cr){
		tree[x].value[dir] = w;
		return;
	}
	PassTag(x, dir);
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(cl <= mid) Change(x*2, cl, cr, dir, w);
	if(cr > mid) Change(x*2+1, cl, cr, dir, w);
	return;
}

inline int Query(int x, int pos, int dir){
	if(tree[x].l == tree[x].r) return tree[x].value[dir];
	PassTag(x, dir);
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(pos <= mid) return Query(x*2, pos, dir);
	else return Query(x*2+1, pos, dir);
}

signed main(){
	n = Read(), m = Read();
	Build(1,1,n);
	for(int i=1; i<=m; i++){
		int k = Read();
		if(visited[k]) continue;
		visited[k] = true;
		int left = Query(1, k, 0), right = Query(1, k+1, 1);
		Change(1, left+1, k, 1, k+1), Change(1, k+1, right-1, 0, k);
		printf("%lld\n", (k-left) * (right-(k+1)));
	}
	return 0;
}