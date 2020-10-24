#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<climits>
#define int long long
#define fake false
using namespace std;
const int MaxN = 502, MaxK = 60;
int n, m, f[MaxK+5][MaxN][2], ans;
bitset<MaxN> g[MaxK+5][2][MaxN][MaxN];
//bool g[MaxK+5][2][MaxN][MaxN];

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
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int x = Read(), y = Read(), w = Read();
		g[0][w][x][y] = 1;
	}
	for(int k=0; k<MaxK; k++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(g[k][0][i][j]) g[k+1][0][i] |= g[k][1][j];
				if(g[k][1][i][j]) g[k+1][1][i] |= g[k][0][j];
//				if(g[k][0][i][j]){
//					for(int l=0; l<MaxN; l++)
//						g[k+1][0][i][l] |= g[k][1][j][l];
//				}
//				if(g[k][1][i][j]){
//					for(int l=0; l<MaxN; l++)
//						g[k+1][1][i][l] |= g[k][0][j][l];
//				}
			}
		}
	}
	memset(f, 128, sizeof(f));
	f[MaxK+1][1][0] = 0ll;
	for(int k=MaxK; k>=0; k--){
		for(int i=1; i<=n; i++){
			f[k][i][0] = f[k+1][i][0];
			f[k][i][1] = f[k+1][i][1];
		}
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(g[k][0][i][j]) f[k][j][1] = max(f[k][j][1], f[k+1][i][0] + (1ll<<k));
				if(g[k][1][i][j]) f[k][j][0] = max(f[k][j][0], f[k+1][i][1] + (1ll<<k));
			}
		}
	}
	for(int i=1; i<=n; i++){
		ans = max(ans, max(f[0][i][0], f[0][i][1]));
	}
	printf("%lld", ans > 1e18 ? -1 : ans);
	return 0;
}