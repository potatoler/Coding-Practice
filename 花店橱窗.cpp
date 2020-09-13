#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 102;
int n, m, a[MaxN][MaxN], f[MaxN][MaxN], ans[MaxN];

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
	m = Read(), n = Read();
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			a[i][j] = Read();
	memset(f, 0xcf, sizeof(f));
	f[0][0] = 0;
	for(int i=1; i<=n; i++)
		for(int j=0; j<=min(i,m); j++){
			if(j == 0) f[i][0] = f[i-1][0];
			else f[i][j] = max(f[i-1][j], f[i-1][j-1]+a[j][i]);
			// printf("%lld ", f[i][j]);
		}
	printf("%lld\n", f[n][m]);
	for(int i=n,j=m; j; ans[j--] = i--)
		while(f[i-1][j] == f[i][j]) --i;
	for(int i=1; i<=m; i++)
		printf("%lld ", ans[i]);
	return 0;
}