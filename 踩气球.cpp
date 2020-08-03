#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, q, a[MaxN], request[MaxN], lastans, ans;

struct SegmentTree{
	int l, r, bolloon;
	vector<int> child;
	vector<int>::iterator it;
}seg[MaxN * 4];

inline int read(){
	char x;
	int num;
	while(x=getchar(),x<'0'||x>'9');
	num=x-'0';
	while(x=getchar(),x>='0'&&x<='9') num*=10,num+=x-'0';
	return num;
}

inline void Build(int x, int l, int r){
	seg[x].l = l, seg[x].r = r;
	if(l == r){
		seg[x].bolloon = a[l];
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	seg[x].bolloon = seg[x*2].bolloon + seg[x*2+1].bolloon;
}

inline void AddChild(int x, int cl, int cr, int id){
	if(seg[x].l == cl && seg[x].r == cr){
		seg[x].child.push_back(id);
		request[id]++;
		return;
	}
	int mid = (seg[x].l + seg[x].r) / 2;
	if(cr <= mid) AddChild(x*2, cl, cr, id);
	else if(cl > mid) AddChild(x*2+1, cl, cr, id);
	else AddChild(x*2, cl, mid, id), AddChild(x*2+1, mid+1, cr, id);
}

inline void Update(int x){
	vector<int>::iterator it;
	for(it=seg[x].child.begin(); it!=seg[x].child.end(); it++){
			request[*it]--;
			if(!request[*it]) ans++; 
	}
}

inline void Change(int x, int pos){
	seg[x].bolloon--;
	if(!seg[x].bolloon) Update(x);
	if(seg[x].l == seg[x].r) return;
	int mid = (seg[x].l + seg[x].r) / 2;
	if(pos <= mid) Change(x*2, pos);
	else Change(x*2+1, pos);
}

signed main(){
	n = read(), m = read();
	for(int i=1;i<=n;i++)
		a[i] = read();
	Build(1, 1, n);
	for(int i=1, a, b; i<=m; i++){
		a = read(), b = read();
		AddChild(1, a, b, i);
	}
	q = read();
	for(int i=1, x; i<=q; i++){
		x = read();
		x=(x + lastans - 1) % n + 1;
		Change(1, x);
		lastans = ans; 
		printf("%lld\n", lastans);
	}
	return 0;
}