#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 300005, MaxM = 1000006;
int n, T, Q;
struct SegmentTree{
	int size, sum, ls, rs;
};
struct Treasure{
	int w, t;
	bool operator < (const Treasure &y) const {
		return w < y.w;
	}
}treasure[MaxN];
int ans[MaxN], root[MaxN];

class PresidentTree{
	private:
	SegmentTree tree[MaxN*30];
	
	public:
	int root[MaxN], cnt;
	
	inline void Insert(int &x, int l, int r, int w){
		int y = x;
		x = ++cnt;
		tree[x] = {tree[y].size+1, tree[y].sum+w, tree[y].ls, tree[y].rs};
		if(l == r) return;
		int mid = (l+r) >> 1;
		if(w <= mid) Insert(tree[x].ls, l, mid, w);
		else Insert(tree[x].rs, mid+1, r, w);
	}
	
	inline int Query(int x, int y, int l, int r, int k){
		if(l == r) return l * k;
		int mid = (l+r) >> 1, rank = tree[tree[x].ls].size - tree[tree[y].ls].size;
		if(k <= rank) return Query(tree[x].ls, tree[y].ls, l, mid, k);
		else return tree[tree[x].ls].sum - tree[tree[y].ls].sum + Query(tree[x].rs, tree[y].rs, mid+1, r, k-rank);
	}
}PT;

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

signed main(){
	n = Read(), T = Read(), Q = Read();
	for(int i=1; i<=n; i++)
		treasure[i] = {Read(), Read()};
	sort(treasure+1, treasure+1+n);
	for(int i=1; i<=n; i++){
		PT.root[i] = PT.root[i-1];
		PT.Insert(PT.root[i], 0, MaxM, treasure[i].t);
	}
	int pos = n;
	for(int i=0; i<=(n-1)/2; i++){
		ans[i] = -1;
		for(pos = min(pos, n-i); pos>i; pos--){
			int tmp = PT.Query(PT.root[pos-1], PT.root[0], 0, MaxM, i) + PT.Query(PT.root[n], PT.root[pos], 0, MaxM, i) + treasure[pos].t;
			if(tmp <= T){
				ans[i] = treasure[pos].w;
				break;
			}
		}
	}
	while(Q--){
		int x = Read();
		x>>=1;
		printf("%lld\n", ans[x]);
	}
	return 0;
}