#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 102, MaxM = 1003, Mod = 998244353;
int n, m, A, ans, f[MaxN][MaxM*2];

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
	freopen("legend.in", "r", stdin);
	freopen("legend.out", "w", stdout);
	n = Read(), m = Read(), A = Read();
	f[0][0] = 0;
	for(int i=1; i<=n; i++){
		for(int j=i; j<m+A; j++){
			int sum = 0;
			for(int k=1; k<=A && j-k>=0; k++){
				sum += f[i-1][j-k];
			}
			f[i][j] = (sum + 1) % Mod;
		}
	}
	for(int i=0; i<=n; i++)
		for(int j=0; j<=m; j++)
			ans += f[i][j];
	printf("%lld", ans);
	return 0;
}