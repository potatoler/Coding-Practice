#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, t[MaxN], f[MaxN], ans;
struct Node{
	int x;
	bool operator < (const Node &y) const {
		return x + t[x] > y.x + t[y.x];
	}
};
int tree[MaxN*4];
priority_queue<Node> q;

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
	tree[x] = max(tree[x<<1], tree[x<<1|1]);
}

inline void Change(int x, int l, int r, int pos, int w){
	if(l == r){
		tree[x] = w;
		return;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid) Change(x<<1, l, mid, pos, w);
	else Change(x<<1|1, mid+1, r, pos, w);
	Update(x);
	return;
}

inline int Query(int x, int l, int r, int ql, int qr){
	if(ql > qr) return 0;
	if(ql <= l && r <= qr) return tree[x];
	int mid = (l+r) >> 1, res = -INT_MAX;
	if(ql <= mid) res = max(res, Query(x<<1, l, mid, ql, qr));
	if(qr > mid) res = max(res, Query(x<<1|1, mid+1, r, ql, qr));
	return res;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)	
		t[i] = Read();
	for(int i=1; i<=n; i++){
		int a = Read();
		f[i] = a * t[i];
		while(q.size()){
			Node cur = q.top();
//			printf("%lld\n", cur.x + t[cur.x]);
			if(cur.x + t[cur.x] > i) break;
			q.pop();
			Change(1, 1, n, cur.x, f[cur.x]);
		}
		f[i] += Query(1, 1, n, 1, i-t[i]);
		ans = max(ans, f[i]);
		q.push((Node){i});
	}
	printf("%lld", ans);
	return 0;
}