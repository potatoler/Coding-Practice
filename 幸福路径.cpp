#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1002;
const double INF = 1e18;
int n, m, v0;
double a[MaxN], f[50][MaxN][MaxN], p, ans=0.0;

signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i=1; i<=n; i++)
		scanf("%lf", &a[i]);
	for(int k=0; k<31; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				f[k][i][j] = -INF;
	scanf("%lld%lf", &v0, &p);
	for(int i=1; i<=m; i++){
		int x,y;
		scanf("%lld%lld", &x, &y);
		f[0][x][y] = p * a[y];
	}
	for(int k=1; k<31; k++, p=p*p){
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++){
				f[k][i][j] = max(f[k-1][i][j], f[k][i][j]);
				for(int l=1; l<=n; l++)
					f[k][i][j] = max(f[k][i][j], f[k-1][i][l] + p*f[k-1][l][j]);
			}
	}
	for(int i=1; i<=n; i++)
		ans = max(ans, f[30][v0][i]);
	ans += a[v0];
	printf("%.1lf", ans);
	return 0;
}