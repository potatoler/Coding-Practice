#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 105;
int n, m, ex, ey, f[2][MaxN][MaxN][MaxN], sum[MaxN][MaxN];
char mp[MaxN][MaxN];

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


inline int Sum(int sx, int sy, int tx, int ty){
	if (sx > tx || sy > ty) return 0;
	return sum[tx][ty] - sum[sx-1][ty] - sum[tx][sy-1] + sum[sx-1][sy-1];
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		scanf("%s", mp[i]+1);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(mp[i][j] == 'o') sum[i][j] = 1;
			else if(mp[i][j] == 'E') ex = i, ey = j;
			sum[i][j] = sum[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			printf("%lld ", sum[i][j]);
//		}
//		printf("\n");
//	}
	
	int ans = 0, p = 0;
	for (int i=0; i<=n; i++){
		memset(f[p^1], 0, sizeof(f[p^1]));
		for (int j=0; j<=m; j++){
			for (int k=0; k<=n; k++){
				for (int l=0; l<=m; l++){
					if (ex+i > n || ex-k < 1 || ey+j > m || ey-l < 1) continue;
					if (ex+i+1 <= n-k) f[p^1][j][k][l] = max(f[p^1][j][k][l], f[p][j][k][l] + Sum(ex+i+1, max(j+1,ey-l), ex+i+1, min(m-l,ey+j)));
					if (ey+j+1 <= m-l) f[p][j+1][k][l] = max(f[p][j+1][k][l], f[p][j][k][l] + Sum(max(i+1,ex-k), ey+(j+1), min(n-k,ex+i), ey+(j+1)));
					if (ex-k-1 >= 1+i) f[p][j][k+1][l] = max(f[p][j][k+1][l], f[p][j][k][l] + Sum(ex-(k+1), max(j+1,ey-l), ex-(k+1), min(m-l,ey+j)));
					if (ey-l-1 >= 1+j) f[p][j][k][l+1] = max(f[p][j][k][l+1], f[p][j][k][l] + Sum(max(i+1,ex-k), ey-(l+1), min(n-k,ex+i), ey-(l+1)));
					ans = max(ans, f[p][j][k][l]);
				}
			}
		}
		p ^= 1;
	}
	printf("%lld", ans);
	return 0;
}