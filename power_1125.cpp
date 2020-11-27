#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 10000007, Mod = 998244353;
int fac[MaxN], inv[MaxN], ans[MaxN];

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
	for (int i = 1; i < MaxN; i++)
		fac[i] = fac[i-1] * i % Mod;
	inv[MaxN-1] = QuickPower(fac[MaxN-1], Mod-2);
	for(int i=MaxN-2; i>=0; i--)
		inv[i] = inv[i+1] * (i+1) % Mod;
}

inline int C(int x, int y){
	if(x < y) return 0;
	return fac[x] * inv[y] % Mod * inv[x-y] % Mod;
}

inline int H(int x){
	if(!x) return 1;
	return (C(2*x, x) + Mod - C(2*x, x-1)) % Mod;
}

signed main(){
//	freopen("power.in", "r", stdin);
//	freopen("power.out", "w", stdout);
	memset(ans, -1, sizeof(ans));
	Init();
	int T = Read();
	while(T--){
		int n = Read();
		if(ans[n] != -1){
			printf("%lld\n", ans[n]);
			continue;
		}
		ans[n] = 0;
		if(n & 1){
			for(int i=1; i<=n; i+=2){
				ans[n] = (ans[n] + H((n-i)/2) * C(n,i) % Mod * i % Mod) % Mod;
			}
		}
		else{
			for(int i=0; i<=n; i+=2){
				ans[n] = (ans[n] + H((n-i)/2) * C(n,i) % Mod * i % Mod) % Mod;
			}
		}
		printf("%lld\n", ans[n]);
	}
	return 0;
}