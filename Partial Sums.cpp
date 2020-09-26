#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 2003, Mod = 1000000007;
int n, k, a[MaxN], sum[MaxN], c[MaxN], inv[MaxN], fac[MaxN];

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
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for(int i=2; i<=n; i++){
		fac[i] = fac[i-1] * i % Mod;
		inv[i] = Mod - (Mod/i) * inv[Mod%i] % Mod;
	}
	c[0] = 1;
	for(int i=1; i<=n; i++)
		c[i] = c[i-1] * (k % Mod + i - 1) % Mod * inv[i] % Mod;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++)
		sum[i] = a[i] = Read();
	if(k){
		Init();
		for(int i=1; i<=n; i++){
			sum[i] = 0;
			for(int j=1; j<=i; j++){
				sum[i] = (sum[i] + c[i-j] * a[j] % Mod) % Mod;
			}
		}
	}
	for(int i=1; i<=n; i++)
		printf("%lld ", sum[i]);
	return 0;
}