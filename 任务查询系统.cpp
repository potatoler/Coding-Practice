#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, inited[MaxN], root[MaxN], ori[MaxN], cntTree, ans = 1;
struct SegmentTree{
	int ls, rs, val, sum;
}tree[MaxN * 100];
vector<int> s[MaxN], e[MaxN];
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

inline void Update(int &x, int l, int r, int pre, int pos, int val){
	x = ++cntTree;
	tree[x] = tree[pre];
	tree[x].val += val;
	tree[x].sum += val * inited[pos];
	if(l == r) return;
	int mid = (l + r) / 2;
	if(pos <= mid) Update(tree[x].ls, l, mid, tree[pre].ls, pos, val);
	else Update(tree[x].rs, mid+1, r, tree[pre].rs, pos, val);
}

inline int Query(int x, int l, int r, int k){
	int num = tree[tree[x].ls].val;
	if(l == r) return tree[x].sum / tree[x].val * k;
	int mid = (l + r) / 2;
	if(k <= num) return Query(tree[x].ls, l, mid, k);
	else return Query(tree[x].rs, mid+1, r, k-num) + tree[tree[x].ls].sum;
}

signed main(){
	m = Read(), n = Read();
	for(int i=1; i<=m; i++){
		int x = Read(), y = Read();
		ori[i] = Read(), inited[i] = ori[i];
		s[x].push_back(i);
		e[y+1].push_back(i);
	}
	sort(inited+1, inited+1+m);
	int size = unique(inited+1, inited+1+m) - inited - 1;
	for(int i=1; i<=n; i++){
		root[i] = root[i-1];
		for(int j=0; j<s[i].size(); j++){
			int p = lower_bound(inited+1, inited+1+size, ori[s[i][j]]) - inited;
			Update(root[i], 1, size, root[i], p, 1);
		}
		for(int j=0; j<e[i].size(); j++){
			int p = lower_bound(inited+1, inited+1+size, ori[e[i][j]]) - inited;
			Update(root[i], 1, size, root[i], p, -1);
		}
	}
	for(int i=1; i<=n; i++){
		int x = Read(), a = Read(), b = Read(), c = Read(), k = (a * ans + b) % c + 1;
		if(k > tree[root[x]].val) ans = tree[root[x]].sum;
		else ans = Query(root[x], 1, size, k);
		printf("%lld\n", ans);
	}
	return 0;
}