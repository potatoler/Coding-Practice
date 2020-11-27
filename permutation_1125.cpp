#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003;
int n, m;
int fac[MaxN], inv[MaxN], ans;

inline int QuickPower(int a, int b){
	int res = 1;
	while(b){
		if(b&1) res = res * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return res;
}

inline void Init(){
	fac[0] = 1;
	for (int i = 1; i < MaxN; i++)
		fac[i] = fac[i-1] * i % m;
	inv[MaxN-1] = QuickPower(fac[MaxN-1], m-2);
	for(int i=MaxN-2; i>=0; i--)
		inv[i] = inv[i+1] * (i+1) % m;
}

inline int C(int x, int y){
	if(x < y) return 0;
	return fac[x] * inv[y] % m * inv[x-y] % m;
}

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

signed main(){
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	n = Read(), m = Read();
	Init();
	for(int k=0; k<n; k++)
		printf("%lld\n", C(n,n-k) * C(n,n-k) % m * fac[k] % m);
	return 0;
}