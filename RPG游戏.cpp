#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
#define fake false
#define lowbit(x) x&(-x)
using namespace std;
const int MaxN = 100005*15;
int n, m, lim, root[MaxN], cntTree, cntSeg=0;
struct SegmentTree{
	int ls, rs, highest;
}tree[MaxN*4];
struct Segment{
	int k, b;
}segment[MaxN];
vector< vector<int> > val, buff, f;

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

inline int Gety(int serial, int x){
	return segment[serial].k * x + segment[serial].b;
}

inline void Change(int &x, int l, int r, int serial){
	if(!x){
		x = ++cntTree;
		tree[x].highest = serial;
		return;
	}
	// optimize below
	if(Gety(tree[x].highest, l) < Gety(serial, l)){
		if(Gety(tree[x].highest, r) < Gety(serial, r)){
			tree[x].highest = serial;
			return;
		}
	}
	else{
		if(Gety(tree[x].highest, r) > Gety(serial, r)) return;
	}
	// optimize above
	int mid = (l+r) >> 1;
	if(segment[tree[x].highest].k < segment[serial].k){
		if(Gety(tree[x].highest, mid) <= Gety(serial, mid)){
			Change(tree[x].ls, l, mid, tree[x].highest);
			tree[x].highest = serial;
		}
		else Change(tree[x].rs, mid+1, r, serial);
	}
	else if(segment[tree[x].highest].k > segment[serial].k){
		if(Gety(tree[x].highest, mid) <= Gety(serial, mid)){
			Change(tree[x].rs, mid+1, r, tree[x].highest);
			tree[x].highest = serial;
		}
		else Change(tree[x].ls, l, mid, serial);
	}
	else if(segment[tree[x].highest].b < segment[serial].b) tree[x].highest = serial;
	return;
}

inline int Ask(int x, int l, int r, int pos){
	if(!x) return 0;
	int res = Gety(tree[x].highest, pos);
	if(l == r) return res;
	int mid = (l+r) >> 1;
	if(pos <= mid) return max(res, Ask(tree[x].ls, l, mid, pos));
	else return max(res, Ask(tree[x].rs, mid+1, r, pos));
}

inline void Modify(int x, int serial){
	while(x<=m){
		Change(root[x], 1, lim, serial);
		x += lowbit(x);
	}
	return;
}

inline int Query(int x, int pos){
	int res = -LLONG_MAX;
	while(x){
		res = max(res, Ask(root[x], 1, lim, pos));
		x -= lowbit(x);
	}
	return res;
}

signed main(){
	n = Read(), m = Read();
	lim = n + m;
	val.resize(n+1);
	buff.resize(n+1);
	f.resize(n+1);
	for(int i=1; i<=n; i++){
		val[i].resize(m+1);
		buff[i].resize(m+1);
		f[i].resize(m+1);
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			buff[i][j] = Read();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			val[i][j] = Read();
	segment[0] = (Segment){0,0};
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(i == 1 && j == 1){
				Modify(1, 0);
				continue;
			}
			cntSeg++;
			f[i][j] = Query(j, i+j);
			segment[cntSeg].k = buff[i][j];
			segment[cntSeg].b = f[i][j] + val[i][j] - buff[i][j] * (i+j);
			Modify(j, cntSeg);
		}
	}
	printf("%lld", f[n][m]);
	return 0;
}