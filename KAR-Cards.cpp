//#pragma GCC optimized(3)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, m, t, a[MaxN][2], seg[MaxN*4][2][2];

inline int read(){
	char x;
	int num;
	while(x=getchar(),x<'0'||x>'9');
	num=x-'0';
	while(x=getchar(),x>='0'&&x<='9') num*=10,num+=x-'0';
	return num;
}

inline void Update(int x, int l, int r){
	int mid = (l + r) / 2;
	seg[x][1][1] = seg[x][0][0] = seg[x][0][1] = seg[x][1][0] = 0;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++){
			if(a[mid][0] <= a[mid+1][0]) seg[x][i][j] |= seg[x*2][i][0] & seg[x*2+1][0][j];
			if(a[mid][1] <= a[mid+1][0]) seg[x][i][j] |= seg[x*2][i][1] & seg[x*2+1][0][j];
			if(a[mid][0] <= a[mid+1][1]) seg[x][i][j] |= seg[x*2][i][0] & seg[x*2+1][1][j];
			if(a[mid][1] <= a[mid+1][1]) seg[x][i][j] |= seg[x*2][i][1] & seg[x*2+1][1][j];
		}
}

inline void Build(int x, int l, int r){
	if(l == r){
		seg[x][1][1] = seg[x][0][0] = 1;
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid), Build(x*2+1, mid+1, r);
	Update(x, l, r);
}

inline void Change(int x, int l, int r, int pos, int u, int v){
	if(l == r){
		a[l][0] = u, a[l][1] = v;
		return;
	}
	int mid = (l + r) / 2;
	if(pos <= mid) Change(x*2, l, mid, pos, u, v);
	else Change(x*2+1, mid+1, r, pos, u, v);
	Update(x, l, r);
}

signed main(){
	n = read();
	for(int i=1;i<=n;i++)
		a[i][0] = read(), a[i][1] = read();
	m = read();
	Build(1, 1, n);
	for(int i=1;i<=m;i+=2){
		int p = read(), q = read();
		int q0 = a[q][0], q1 = a[q][1], p0 = a[p][0], p1 = a[p][1];
		Change(1, 1, n, p, q0, q1);
		Change(1, 1, n, q, p0, p1);
		if(seg[1][1][1] + seg[1][0][0] + seg[1][0][1] + seg[1][1][0] >= 1) printf("TAK\n");
		else printf("NIE\n");
		
		p = read(), q = read();
		q0 = a[q][0], q1 = a[q][1], p0 = a[p][0], p1 = a[p][1];
		Change(1, 1, n, p, q0, q1);
		Change(1, 1, n, q, p0, p1);
		if(seg[1][1][1] + seg[1][0][0] + seg[1][0][1] + seg[1][1][0] >= 1) printf("TAK\n");
		else printf("NIE\n");
		
//		for(int i=1;i<=n*4;i++)
//			printf("%lld ", seg[i][1][1] + seg[i][0][0] + seg[i][0][1] + seg[i][1][0]);
//		printf("\n");
	}
	return 0;
}