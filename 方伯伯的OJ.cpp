#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<map>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, cntTree, ans, root, L, R;
map<int,int> ID, ID2;
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

inline void Insert(int &x, int l, int r, int pos){
	if(!x) x = ++cntTree;
	tree[x].sum++;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(pos <= mid) Insert(tree[x].ls, l, mid, pos);
	else Insert(tree[x].rs, mid+1, r, pos);
	return;
}

inline int Ask(int x, int l, int r, int pos){
	if(!tree[x].sum || l == r) return 0;
	int mid = (l + r) >> 1;
	if(pos <= mid) return Ask(tree[x].ls, l, mid, pos);
	else return Ask(tree[x].rs, mid+1, r, pos) + tree[tree[x].ls].sum;
}

inline int Find(int x, int k, int l, int r){
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int rank = max((long long)0, min(R,mid) - max(L,l) + 1 - tree[tree[x].ls].sum);
	return rank >= k ? Find(tree[x].ls, k, l, mid) : Find(tree[x].rs, k-rank,  mid+1, r);
}

inline void LevelUp(int x){
	int cur = 0;
	if(ID.find(x) == ID.end()) cur = x;
	else cur = ID[x];
	ans = cur - L + 1 - Ask(root, -INT_MAX, INT_MAX, cur);
	Insert(root, -INT_MAX, INT_MAX, cur);
	ID[x] = --L;
	ID2[L] = x;
}

inline void LevelDown(int x){
	int cur = 0;
	if(ID.find(x) == ID.end()) cur = x;
	else cur = ID[x];
	ans = cur - L + 1 - Ask(root, -INT_MAX, INT_MAX, cur);
	Insert(root, -INT_MAX, INT_MAX, cur);
	ID[x] = ++R;
	ID2[R] = x;
}

inline void Change(int x, int y){
	int cur = 0;
	if(ID.find(x) == ID.end()) cur = x;
	else cur = ID[x];
	ans = cur - L + 1 - Ask(root, -INT_MAX, INT_MAX, cur);
	ID[y] = cur;
	ID2[cur] = y;
}

inline void Query(int x){
	ans = Find(root, x, -INT_MAX, INT_MAX);
	if(ID2.find(ans) != ID2.end()) ans = ID2[ans];
	return;
}

signed main(){
	n = Read(), m = Read();
	L = 1, R = n;
	while(m--){
		int op = Read(), x = Read();
		if(op == 1){
			int y = Read();
			Change(x-ans, y-ans);
			printf("%lld\n", ans);
		}
		if(op == 2){
			LevelUp(x-ans);
			printf("%lld\n", ans);
		}
		if(op == 3){
			LevelDown(x-ans);
			printf("%lld\n", ans);
		}
		if(op == 4){
			Query(x-ans);
			printf("%lld\n", ans);
		}
	}
	return 0;
}