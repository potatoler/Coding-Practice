#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<cstring>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, m, q, cntTree, root[MaxN], pos, lim;
vector<int> v[MaxN];
struct SegmentTree{
	int ls, rs, sum;
}tree[MaxN * 20];

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

inline void Update(int &x, int l, int r, int pos){
	if(!x) x = ++cntTree;
	tree[x].sum++;
	if(l == r) return;
	int mid = (l+r) >> 1;
	if(pos <= mid) Update(tree[x].ls, l, mid, pos);
	else Update(tree[x].rs, mid+1, r, pos);
	return;
}

inline int Query(int x, int l, int r, int w){
	if(l == r) return l;
	int mid = (l+r) >> 1, tmp = mid-l+1-tree[tree[x].ls].sum;
	if(w<=tmp) return Query(tree[x].ls, l, mid, w);
	else return Query(tree[x].rs, mid+1, r, w-tmp);
}

inline int Work1(int x, int y){
	pos = Query(root[n+1], 1, lim, x);
	Update(root[n+1], 1, lim, pos);
	int ans = pos<=n? pos*m : v[n+1][pos-n-1];
	v[n+1].push_back(y?y:ans);
	return ans;
}

inline int Work2(int x, int y){
	pos = Query(root[x], 1, lim, y);
	Update(root[x], 1, lim, pos);
	int ans = pos<m? (x-1)*m+pos : v[x][pos-m];
	v[x].push_back(Work1(x,ans));
	return ans;
}

signed main(){
	n = Read(), m = Read(), q = Read();
	lim = max(n,m) + q;
	while(q--){
		int x = Read(), y = Read();
		printf("%lld\n", y==m? Work1(x,0) : Work2(x,y));
	}
	return 0;
}