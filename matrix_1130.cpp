#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 1000000007;
int fac[MaxN], inv[MaxN];

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

inline int QuickPower(int a, int b){
	int res = 1;
	while(b){
		if(b&1) res = res * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return res;
}

inline void Init(){
	fac[0] = 1;
	for(int i=1; i<MaxN; i++)
		fac[i] = fac[i-1] * i % Mod;
	inv[MaxN-1] = QuickPower(fac[MaxN-1], Mod-2);
	for(int i=MaxN-1; i; i--)
		inv[i-1] = inv[i] * i % Mod;
	return;
}

inline int C(int x, int y){
	return fac[x] * inv[y] % Mod * inv[x-y] % Mod;
}

inline int Calculate(int n, int m, int k){
	int N = 0, M = 0;
	for(int i=0; i<=min(n,k); i++)
		if((i&1) == (k&1)) N = (N + C(n,i)) % Mod;
	for(int j=0; j<=min(m,k); j++)
		if((j&1) == (k&1)) M = (M + C(m,j)) % Mod;
	int all = N * M % Mod;
	N = 0, M = 0;
	if(!(n&1) && !(m&1)){
		for(int i=0; i<=min(n,k); i++)
			if((i&1) == (k&1) && n-i <= k) N = (N + C(n,i)) % Mod;
		for(int j=0; j<=min(m,k); j++)
			if((j&1) == (k&1) && m-j <= k) M = (M + C(m,j)) % Mod;
	}
	int sm = N * M % Mod * QuickPower(2,Mod-2) % Mod;
	return (all - sm + Mod) % Mod;
}

signed main(){
	Init();
	int T = Read();
	while(T--){
		int n = Read(), m = Read(), k = Read();
		printf("%lld\n", Calculate(n,m,k));
	}
	return 0;
}