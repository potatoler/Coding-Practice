#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2000;
double v[MaxN][MaxN];
int n, k, t[MaxN], x[MaxN], y[MaxN], f[MaxN], cnt;
struct Path{
	double velocity;
	int dist2, time;
	bool operator < (const Path &b) const{
		return velocity < b.velocity;
	}
}path[MaxN*MaxN];

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

inline int GCD(int a, int b){
	if(b == 0) return a;
	else return GCD(b, a%b);
}

inline bool Check(int cur){
	double dis = path[cur].velocity;
	memset(f, 0, sizeof(f));
	for(int i=1; i<=n; i++){
		for(int j=0; j<=i-1; j++){
			if(v[i][j] <= dis) f[i] = max(f[i], f[j]+1);
		}
		if(f[i] >= k) return true;
	}
	return false;
}

inline void Calculate(int ansDist2, int ansTime){
	int b = ansDist2, a = 1, c = ansTime;
	for(int i=2; i*i<=ansDist2; i++){
		while(b % (i*i) == 0){
			b /= (i*i);
			a *= i;
		}
	}
	int gcd = GCD(a, c);
//	printf("%lld\n", gcd);
	a /= gcd, c /= gcd;
	printf("%lld %lld %lld", a, b, c);
	return;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		t[i] = Read(), x[i] = Read(), y[i] = Read();
	}
	for(int i=0; i<=n-1; i++){
		for(int j=i+1; j<=n; j++){
			cnt++;
			path[cnt].dist2 = (x[i]-x[j]) * (x[i]-x[j]) + (y[i]-y[j]) * (y[i]-y[j]);
			path[cnt].time = t[j] - t[i];
			path[cnt].velocity = v[i][j] = v[j][i] = 1.0 * sqrt(path[cnt].dist2) / path[cnt].time;
		}
	}
	sort(path+1, path+1+cnt);
	int l = 1, r = cnt;
	while(l < r){
		int mid = (l+r) >> 1;
		if(Check(mid)) r = mid;
		else l = mid+1;
	}
//	printf("%lld %lld\n", path[r].dist2, path[r].time);
	Calculate(path[r].dist2, path[r].time);
	return 0;
}