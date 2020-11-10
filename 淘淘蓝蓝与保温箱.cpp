#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100;
int n, q, a[MaxN], b[MaxN], f[MaxN][MaxN*MaxN/4], ans[MaxN];

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
	n = Read();
	int suma = 0, sumb = 0;
	for (int i=1; i<=n; i++) 
		a[i] = Read(), suma += a[i];
	for (int i=1;i<=n;i++)
		b[i] = Read(), sumb += b[i];
	for(int i=0; i<=n; i++)
		for(int j=0; j<=sumb; j++)
			f[i][j] = -INT_MAX;
	f[0][0] = 0;
	for(int i=1; i<=n; i++)
		for(int j=i; j>=1; j--)
			for (int k=b[i]; k<=sumb; k++)
				f[j][k] = max(f[j][k], f[j-1][k-b[i]] + a[i]);
	for(int i=0; i<=n; i++) 
		ans[i] = -1;
	for(int i=1; i<=n; i++)
		for(int j=suma; j<=sumb; j++)
			ans[i] = max(ans[i], f[i][j]);
	q = Read();
	while(q--){
		int k = Read();
		if(ans[k] == -1){
			printf("-1\n");
			continue;
		}
		else printf("%lld\n", suma - ans[k]);
	}
	return 0;
}