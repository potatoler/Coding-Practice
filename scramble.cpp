#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long 
using namespace std;
int T, n, m, k;

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

inline int QuickPower(int x, int y, int mod){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

signed main(){
	freopen("scramble.in", "r", stdin);
	freopen("scramble.out", "w", stdout);
	T = Read();
	while(T--){
		n = Read(), m = Read(), k = Read();
		int tmp = QuickPower(2, k, n+m);
		int ans = min(n*tmp%(n+m), m*tmp%(n+m));
		printf("%lld\n", ans);
	}
	return 0;
}