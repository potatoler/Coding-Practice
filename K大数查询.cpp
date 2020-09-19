#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;
const int MaxN = 50004;
int n, m;

struct Outer_Segment_Tree{
	int ls, rs, sum, add;
}outer_tree[MaxN*17*17];

int cnt;
struct Inner_Sgenment_Tree{
	int l, r, serial;
}inner_tree[MaxN*4];

struct Query{
	int op, a, b, c;
}query[MaxN];
vector<int> question;

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

inline int Get(int x){
	return lower_bound(question.begin(), question.end(), x) - question.begin();
}

inline int Intersection(int l, int r, int ll, int rr){
	return min(r, rr) - max(l, ll) + 1;
}

inline void Build(int x, int l, int r){
	inner_tree[x].l = l, inner_tree[x].r = r, inner_tree[x].serial = ++cnt;
	if(l == r) return;
	int mid = (l + r) >> 1;
	Build(x<<1, l, mid), Build(x<<1|1, mid+1, r);
	return;
}

inline void Update(int x, int l, int r, int ll, int rr){
	outer_tree[x].sum += Intersection(l, r, ll, rr);
	if(ll <= l && r <= rr){
		outer_tree[x].add++;
		return;
	}
	int mid = (l + r) >> 1;
	if(ll <= mid){
		if(!outer_tree[x].ls) outer_tree[x].ls = ++cnt;
		Update(outer_tree[x].ls, l, mid, ll, rr);
	}
	if(rr > mid){
		if(!outer_tree[x].rs) outer_tree[x].rs = ++cnt;
		Update(outer_tree[x].rs, mid+1, r, ll, rr);
	}
	return;
}

inline void Change(int x, int l, int r, int pos){
	Update(inner_tree[x].serial, 1, n, l, r);
	if(inner_tree[x].l == inner_tree[x].r) return;
	int mid = (inner_tree[x].l + inner_tree[x].r) >> 1;
	if(pos <= mid) Change(x<<1, l, r, pos);
	else Change(x<<1|1, l, r, pos);
	return;
}

inline int Sum(int x, int l, int r, int ll, int rr, int add){
	if(ll <= l && r <= rr) return outer_tree[x].sum + (r-l+1) * add;
	int mid = (l + r) >> 1, ans = 0;
	add += outer_tree[x].add;
	if(ll <= mid){
		if(outer_tree[x].ls) ans += Sum(outer_tree[x].ls, l, mid, ll, rr, add);
		else ans += Intersection(l, mid, ll, rr) * add;
	}
	if(rr > mid){
		if(outer_tree[x].rs) ans += Sum(outer_tree[x].rs, mid+1, r, ll, rr, add);
		else ans += Intersection(mid+1, r, ll, rr) * add;
	}
	return ans;
}

inline int Ask(int x, int l, int r, int rank){
	if(inner_tree[x].l == inner_tree[x].r) return inner_tree[x].r;
	int mid = (inner_tree[x].l + inner_tree[x].r) >> 1;
	int tmp = Sum(inner_tree[x<<1|1].serial, 1, n, l, r, 0);
	if(tmp >= rank) return Ask(x<<1|1, l, r, rank);
	else return Ask(x<<1, l, r, rank-tmp);
}

signed main(){
	n = Read(), m = Read();
	for(int i=0; i<m; i++){
		query[i].op = Read(), query[i].a = Read(), query[i].b = Read(), query[i].c = Read();
		if(query[i].op == 1) question.push_back(query[i].c);
	}
	sort(question.begin(), question.end());
	question.erase(unique(question.begin(), question.end()), question.end());
	Build(1, 0, question.size()-1);
	for(int i=0; i<m; i++){
		int op = query[i].op, a = query[i].a, b = query[i].b, c = query[i].c;
		if(op == 1) Change(1, a, b, Get(c));
		else printf("%d\n", question[Ask(1, a, b, c)]);	
	}
	return 0;
}