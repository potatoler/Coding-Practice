#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 20000007, Mod = 1000000007;
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

inline int QuickPower(int x, int y){
	int ans = 1;
	while(y){
		if(y & 1) ans = 1ll * ans * x % Mod;
		x = 1ll * x * x % Mod;
		y >>= 1;
	}
	return ans;
}

inline void Init(){
	fac[0] = inv[0] = 1;
	for(int i=1; i<MaxN; i++)
		fac[i] = 1ll * fac[i-1] * i % Mod;
	inv[MaxN-1] = QuickPower(fac[MaxN-1], Mod-2);
	for(int i=MaxN-2; i>=1; i--)
		inv[i] = 1ll * inv[i+1] * (i+1) % Mod;
	return;
}

inline int C(int n, int m){
	if(n < m) return 0;
	return 1ll * fac[n] * inv[m] % Mod * inv[n-m] % Mod;
}

int main(){
	Init();
	int T = Read();
	while(T--){
		int n = Read(), x = Read(), y = Read();
		if(x > y) swap(x,y);
		long long ans1 = (C(x+y-2, x-1) - C(x+y-2, x-2) + Mod) % Mod;
		long long ans2 = (C(2*n-x-y, n-y) - C(2*n-x-y, n-y-1) + Mod) % Mod;
		printf("%lld\n", ans1*ans2%Mod);
	}
	return 0;
}