#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 42, MaxD = 100005, Mod = 1000000007;
int n, d, ans, r[MaxN], fac[MaxD], inv[MaxD], f[MaxN][MaxN][MaxN*MaxN];

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
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans;
}

inline void Init(){
	fac[0] = 1;
	for(int i=1; i<MaxD; i++)
		fac[i] = fac[i-1] * i % Mod;
	inv[MaxD-1] = QuickPower(fac[MaxD-1], Mod-2);
	for(int i=MaxD-2; i>=0; i--)
		inv[i] = inv[i+1] * (i+1) % Mod;
	return;
}

inline int C(int n, int m){
	return fac[n] * inv[m] % Mod * inv[n-m] % Mod;
}

signed main(){
	Init();
	n = Read(), d = Read();
	for(int i=1; i<=n; i++)
		r[i] = Read();
	sort(r+1, r+1+n);
	f[0][0][0] = 1;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=i; j++){
			for(int k=0; k<MaxN*MaxN; k++){
				f[i+1][j+1][k+1] = (f[i+1][j+1][k+1] + f[i][j][k]) % Mod;
				if(j>0) f[i+1][j][k+r[i+1]] = (f[i+1][j][k+r[i+1]] + 2 * j * f[i][j][k]) % Mod;
				if(j>1) f[i+1][j-1][k+2*r[i+1]-1] = (f[i+1][j-1][k+2*r[i+1]-1] + j * (j-1) * f[i][j][k]) % Mod;
			}
		}
	}
	for(int i=0; i<=min(d, MaxN*MaxN); i++)
		ans = (ans + C(d-i+n,n) * f[n][1][i] % Mod) % Mod;
	printf("%lld", ans);
	return 0;
}