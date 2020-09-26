#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxM = 100005, MaxP = 2003, Mod = 1000000007;
int n, m, ans, f[MaxP][MaxP], sval, mn;
char s[MaxM];

signed main(){
	scanf("%lld%lld%s", &n, &m, s+1);
	for(int i=1; i<=m; i++){
		if(s[i] == '(') sval++;
		else sval--;
		mn = min(mn, sval);
	}
	f[0][0] = 1;
	for(int i=1; i<=n-m; i++){
		for(int j=0; j<=i; j++){
			f[i][j] = f[i-1][j+1];
			if(j) f[i][j] = (f[i][j] + f[i-1][j-1]) % Mod;
		}
	}
	for(int i=0; i<=n-m; i++){
		for(int j=0; j<=i; j++){
			if(j+sval <= n-m && j+mn >= 0) ans = (ans + (f[i][j] * f[n-m-i][sval+j]) % Mod) % Mod;
		}
	}
	printf("%lld", ans);
	return 0;
}