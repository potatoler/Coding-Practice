#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2003;
int n, t;
double ans, f[MaxN][MaxN], p;

signed main(){
	scanf("%lld%lf%lld", &n, &p, &t);
	double q = 1.0-p;
	f[0][0] = 1;
	for(int i=1; i<=n; i++)
		f[0][i] = 0;
	for(int i = 1; i<=t; i++)
		f[i][0] = q * f[i-1][0];
	for(int i=1; i<=t; i++)
		for(int j=1; j<n; j++)
			f[i][j] = p * f[i-1][j-1] + q * f[i-1][j];
	for(int i=1; i<=t; i++)
		f[i][n] = f[i-1][n] + p * f[i-1][n-1];
	for(int i=1; i<=n; i++)
		ans += f[t][i] * i;
	printf("%.7lf", ans);
	return 0;
}