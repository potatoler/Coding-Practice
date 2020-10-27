#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, Inf = LLONG_MAX, MaxH = 1000000;
int n, lowest[MaxH*4+10], h[MaxN], k[MaxN], b[MaxN], sum[MaxN], f[MaxN];

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
	return k[serial] * x + b[serial];
}

inline void Change(int x, int l, int r, int serial){
	if(l == r){
		if(Gety(serial, l), Gety(lowest[x], l)) lowest[x] = serial;
		return;
	}
	int mid = (l+r) >> 1;
	if(k[serial] < k[lowest[x]]){
		if(Gety(serial, mid) <= Gety(lowest[x], mid)){
			Change(x<<1, l, mid, lowest[x]);
			lowest[x] = serial;
		}
		else Change(x<<1|1, mid+1, r, serial);
	}
	else if(k[serial] > k[lowest[x]]){
		if(Gety(serial, mid) <= Gety(lowest[x], mid)){
			Change(x<<1|1, mid+1, r, lowest[x]);
			lowest[x] = serial;
		}
		else Change(x<<1, l, mid, serial);
	}
	else if(b[serial] < b[lowest[x]]) lowest[x] = serial;
	return;
}

inline int Query(int x, int l, int r, int pos){
	if(l == r) return Gety(lowest[x], pos);
	int mid = (l+r) >> 1;
	int res = Gety(lowest[x], pos);
	if(pos <= mid) return min(res, Query(x<<1, l, mid, pos));
	else return min(res, Query(x<<1|1, mid+1, r, pos));
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		h[i] = Read();
	for(int i=1; i<=n; i++)
		sum[i] = sum[i-1] + Read();
	f[1] = 0;
	b[0] = Inf;
	k[1] = -2 * h[1];
	b[1] = h[1]*h[1] - sum[1] + f[1];
	Change(1, 0, MaxH, 1);
	for(int i=2; i<=n; i++){
		f[i] = Query(1, 0, MaxH, h[i]) + sum[i-1] + h[i]*h[i];
		k[i] = -2 * h[i];
		b[i] = h[i]*h[i] - sum[i] + f[i];
		Change(1, 0, MaxH, i);
	}
	printf("%lld", f[n]);
	return 0;
}