#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, highest[50000*4], cntSeg;
double k[MaxN], b[MaxN];
char opt[15];

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

inline double Gety(int serial, int x){
	return k[serial] * (x-1) + b[serial];
}

inline void Change(int x, int l, int r, int serial){
	if(l == r){
		if(Gety(highest[x], l) < Gety(serial, l)) highest[x] = serial;
		return;
	}
	if(!highest[x]){
		highest[x] = serial;
		return;
	}
	int mid = (l+r) >> 1;
	double cury = Gety(highest[x], mid), newy = Gety(serial, mid);
	if(k[highest[x]] < k[serial]){
		if(cury <= newy){
			Change(x<<1, l, mid, highest[x]);
			highest[x] = serial;
		}
		else Change(x<<1|1, mid+1, r, serial);
	}
	else if(k[highest[x]] > k[serial]){
		if(cury <= newy){
			Change(x<<1|1, mid+1, r, highest[x]);
			highest[x] = serial;
		}
		else Change(x<<1, l, mid, serial);
	}
	else if(b[highest[x]] > b[serial]) highest[x] = serial;
	return;
}

double Query(int x, int l, int r, int pos){
	if(!cntSeg) return 0.0;
	if(l == r) return Gety(highest[x], l);
	double res = Gety(highest[x], pos);
	int mid = (l+r) >> 1;
	if(pos <= mid) res = max(res, Query(x<<1, l, mid, pos));
	else res = max(res, Query(x<<1|1, mid+1, r, pos));
	return res;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		scanf("%s", opt);
		if(opt[0] == 'Q'){
			int t = Read();
			printf("%lld\n", (int)Query(1, 1, 50000, t) / 100);
		}
		else{
			cntSeg++;
			scanf("%lf%lf", &b[cntSeg], &k[cntSeg]);
			Change(1, 1, 50000, cntSeg);
		}
	}
	return 0;
}