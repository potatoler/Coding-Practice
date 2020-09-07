#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, m, q, cntTree, root[MaxN];
vector<int> v[MaxN];
struct SegmentTree{
	int ls, rs, sum;
}tree[MaxN * 25];

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

inline void Update(int &x, int l, int r, int p){
	if(!x) x = ++cntTree;
	tree[x].sum++;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p < mid) Update(tree[x].ls, l, mid, p);
	else Update(tree[x].rs, mid+1, r, p);
	return;
}