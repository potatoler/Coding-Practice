#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1503;
int n, m, k, sum[MaxN][MaxN], sq[MaxN][MaxN], ans;
int rb[MaxN][MaxN], lb[MaxN][MaxN], rt[MaxN][MaxN], lt[MaxN][MaxN];

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
	n = Read(), m = Read(), k = Read();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			int val = Read();
			sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + val;
		}
	}
	
	for(int i=k; i<=n; i++)
		for(int j=k; j<=m; j++)
			sq[i][j] = sum[i][j] - sum[i-k][j] - sum[i][j-k] + sum[i-k][j-k];
			
	for(int i=k; i<=n; i++)
		for(int j=k; j<=m; j++)
			rb[i][j] = max(sq[i][j], max(rb[i-1][j], rb[i][j-1]));
			
	for(int i=k; i<=n; i++)
		for(int j=m-k+1; j; j--)
			lb[i][j] = max(sq[i][j+k-1], max(lb[i-1][j], lb[i][j+1]));
			
	for(int i=n-k+1; i; i--)
		for(int j=k; j<=m; j++)
			rt[i][j] = max(sq[i+k-1][j], max(rt[i+1][j], rt[i][j-1]));
	
	for(int i=n-k+1; i; i--)
		for(int j=m-k+1; j; j--)
			lt[i][j] = max(sq[i+k-1][j+k-1], max(lt[i+1][j], lt[i][j+1]));
			
	for(int i=k; i<=n; i++)
		for(int j=k+k; j<=m-k; j++)
			ans = max(ans, sq[i][j] + rb[n][j-k] + lb[n][j+1]);
			
	for(int i=k+k; i<=n-k; i++)
		for(int j=k; j<=m; j++)
			ans = max(ans, sq[i][j] + rb[i-k][m] + rt[i+1][m]);
	
	for(int i=k; i<=n-k; i++)
		for(int j=k; j<=m-k; j++)
			ans = max(ans, rb[i][j] + rt[i+1][j] + lt[1][j+1]);
	
	for(int i=k; i<=n-k; i++)
		for(int j=k; j<=m-k; j++)
			ans = max(ans, rb[n][j] + lb[i][j+1] + lt[i+1][j+1]);
	
	for(int i=k; i<=n-k; i++)
		for(int j=k; j<=m-k; j++)
			ans = max(ans, rb[i][j] + lb[i][j+1] + lt[i+1][1]);
	
	for(int i=k; i<=n-k; i++)
		for(int j=k; j<=m-k; j++)
			ans = max(ans, rb[i][m] + rt[i+1][j] + lt[i+1][j+1]);
			
	printf("%lld", ans);
	return 0;
}