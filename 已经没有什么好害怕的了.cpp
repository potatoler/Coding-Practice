#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2003, Mod = 1000000009;
int n, k, ans, a[MaxN], b[MaxN], pos[MaxN], fac[MaxN], inv[MaxN], f[MaxN][MaxN], g[MaxN];

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
	ans = 1;
	while(y){
		if(y&1) ans = ans * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return ans;
}

inline void Init(){
	fac[0] = inv[0] = inv[1] = 1;
	for(int i=1; i<MaxN; i++)
		fac[i] = fac[i-1] * i % Mod;
	for(int i=2; i<MaxN; i++)
		inv[i] = (Mod-Mod/i) * inv[Mod%i] % Mod;
	for(int i=2; i<MaxN; i++)
		inv[i] = inv[i-1] * inv[i] % Mod;
	return;
}

inline int C(int n, int m){
	return fac[n] * inv[m] % Mod * inv[n-m] % Mod;
}

signed main(){
	Init();
	n = Read(), k = Read();
	if((n+k) & 1){
		printf("0");
		return 0;
	}
	k = (n+k) / 2;
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=n; i++)
		b[i] = Read();
	sort(a+1, a+1+n);
	sort(b+1, b+1+n);
	int p = 0;
	for(int i=1; i<=n; i++){
		while(p < n && b[p+1] < a[i])
			p++;
		pos[i] = p;
	}
	f[0][0] = 1;
	for(int i=1; i<=n ;i++){
		f[i][0] = f[i-1][0];
		for(int j=1; j<=i; j++)
			f[i][j] = (f[i-1][j] + f[i-1][j-1] * max(0ll, pos[i]-j+1) % Mod) % Mod;
	}
	for (int i=k; i<=n; i++){
		if ((i-k) % 2 == 0) ans = (ans + ((((C(i,k) * f[n][i]) % Mod) * fac[n-i]) % Mod)) % Mod;
		else ans = (ans - ((((C(i,k) * f[n][i]) % Mod) * fac[n-i]) % Mod) + Mod) % Mod;
	}
	printf("%lld", ans);
	return 0;
}