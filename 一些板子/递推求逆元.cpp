#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 3000006;
int n, p, fac[MaxN], inv[MaxN];

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

inline int QuickPower(int a, int b, int mod){
	int res = 1;
	while(b){
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

signed main(){
	n = Read(), p = Read();
	fac[0] = 1;
	for(int i=1; i<=n; i++)
		fac[i] = fac[i-1] * i % p;
	inv[n] = QuickPower(fac[n], p-2, p);
	for(int i=n-1; i>=1; i--)
		inv[i] = inv[i+1] * (i+1) % p;
	for(int i=1; i<=n; i++)
		inv[i] = fac[i-1] * inv[i] % p;
	for(int i=1; i<=n; i++)
		printf("%lld\n", inv[i]);
	return 0;
}