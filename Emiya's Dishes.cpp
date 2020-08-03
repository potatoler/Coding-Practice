#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MaxN = 105, MaxM = 2005, Mod = 998244353;
int n, m;
ll ans = 1, cnt[MaxN], w[MaxN][MaxM], f[MaxN][MaxM];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&w[i][j]);
			cnt[i] = (cnt[i] + w[i][j]) % Mod;
		}
		ans = (ans * (cnt[i] + 1)) % Mod;
	}
	ans = (ans + Mod - 1) % Mod;
	for(int i=1;i<=m;i++){
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int j=1;j<=n;j++){
			for(int k=0;k<=2*(j-1);k++){
				f[j][k] = (f[j][k] + f[j-1][k] * (cnt[j] - w[j][i])) % Mod;
				f[j][k+1] = (f[j][k+1] + f[j-1][k]) % Mod;
				f[j][k+2] = (f[j][k+2] + f[j-1][k] * w[j][i]) % Mod;
			}
		}
		for(int j=n+1;j<=2*n;j++)
			ans = (ans + Mod - f[n][j]) % Mod;
	}
	printf("%lld", ans);
	return 0;
}