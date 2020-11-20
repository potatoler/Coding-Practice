#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003, Mod = 1000000000;
int n, m, a, b, f[MaxN][MaxN], sumf[MaxN][MaxN], g[MaxN][MaxN], sumg[MaxN][MaxN], ans;

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
	n = Read(), m = Read(), a = Read(), b = Read();
	f[0][0] = sumf[0][0] = 1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=i; j++){
			if(i-a <= 0) f[i][j] = sumf[i-1][j-1];
			else f[i][j] = (sumf[i-1][j-1] - sumf[i-a-1][j-1] + Mod) % Mod;
		}
		for(int j=0; j<=i; j++)
			sumf[i][j] = (sumf[i-1][j] + f[i][j]) % Mod;
	}
	g[0][0] = sumg[0][0] = 1;
	for(int i=1; i<=m; i++){
		for(int j=1; j<=i; j++){
			if(i-b <= 0) g[i][j] = sumg[i-1][j-1];
			else g[i][j] = (sumg[i-1][j-1] - sumg[i-b-1][j-1] + Mod) % Mod;
		}
		for(int j=0; j<=i; j++)
			sumg[i][j] = (sumg[i-1][j] + g[i][j]) % Mod;
	}
	for(int i=1; i<=min(n,a); i++)
		for(int j=1; j<=min(m,n-i+1); j++)
			ans = (ans + i * (g[m][j] * f[n-i][j-1] % Mod) % Mod) % Mod;
	for(int i=1; i<=min(m,b); i++)
		for(int j=1; j<=min(n,m-i+1); j++)
			ans = (ans + i * (f[n][j] * g[m-i][j-1] % Mod) % Mod) % Mod;
	printf("%lld", ans);
	return 0;
}