#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int Mod = 100000000;
int n, m, f[15][1<<15], field[15], ans;

signed main(){
	scanf("%lld%lld", &m, &n);
	for(int i=1;i<=m;i++){
		for(int j=0;j<n;j++){
			int x;
			scanf("%lld", &x);
			field[i] |= (x << j);
		}
	}
	for(int i=0;i<(1<<n);i++){
		if(i&(i>>1)) continue;
		if((field[1] | i) != field[1]) continue;
		f[1][i] = 1;
	}
	for(int i=2;i<=m;i++){
		for(int j=0;j<(1<<n);j++){
			if(j & (j>>1)) continue;
			if((field[i]|j) != field[i]) continue;
			for(int k=0;k<(1<<n);k++){
				if(k & (k>>1)) continue;
				if((field[i-1] | k) != field[i-1]) continue;
				if(k & j) continue;
				f[i][j] = (f[i][j] + f[i-1][k]) % Mod;
			}
		}
	}
	for(int i=0;i<(1<<n);i++)
		ans = (ans + f[m][i]) % Mod;
	printf("%lld", ans);
	return 0;
}