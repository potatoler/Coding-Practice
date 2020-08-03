#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
const int MaxN = 1005, Mod = 10000;
int n, k, f[MaxN][MaxN];

signed main(){
	scanf("%lld%lld", &n, &k);
	f[1][0] = 1;
	for(int i=2;i<=n;i++){
		int sum = 0;
		for(int j=0; j<=k; j++){
			sum += f[i-1][j];
			f[i][j] = sum;
			if(j>=i-1) sum = (sum - f[i-1][j-i+1] + Mod) % Mod;
			sum = (sum + Mod) % Mod;
		}
	}	
	printf("%lld", f[n][k] % Mod);
}