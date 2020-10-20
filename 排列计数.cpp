#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1000006, Mod = 1000000007;
int T, N, M, fac[MaxN], inv[MaxN], D[MaxN];

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

inline void Init(){
	fac[0] = 1;
	for(int i=1; i<MaxN; i++)
		fac[i] = fac[i-1] * i % Mod;
	D[0] = 1, D[1] = 0, D[2] = 1;
	for(int i=3; i<MaxN; i++)
		D[i] = (i-1) * (D[i-1] + D[i-2]) % Mod;
	return;
}

inline int QuickPower(int a, int b){
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans;
}

inline int C(int n, int m){
	if(m == 0) return 1;
	return fac[n] * QuickPower(fac[m], Mod-2) % Mod * QuickPower(fac[n-m], Mod-2) % Mod;
}

signed main(){
	Init();
	T = Read();
	while(T--){
		N = Read(), M = Read();
		int ans = C(N,M) * D[N-M] % Mod;
		printf("%lld\n", ans);
	}
	return 0;
}
