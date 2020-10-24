#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 51, Mod = 998244353;
int T, n, m, f[MaxN][MaxN][MaxN*MaxN], g[MaxN][MaxN], map[MaxN][MaxN];

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

inline int GCD(int x, int y){
	if(!y) return x;
	return GCD(y, x%y);
}

signed main(){
	T = Read();
	while(T--){
		n = Read(), m = Read();
		int d = GCD(n, m), ans = 0;
		for(int i=1; i<=n; i++){
			char c = ' ';
			while(c < '0' || c > '9'){
				c = getchar();
			}
			for(int j=1; j<=m; j++){
				map[i][j] = c - '0';
				c = getchar();
			}
		}		
		for(int dx=0; dx<=d; dx++){
			int dy = d - dx;
			if(GCD(dx, n) == 1 && GCD(dy, m) == 1 && GCD(dx, dy) == 1){
				for(int i=1; i<=dx+1; i++){
					for(int j=1; j<=dy+1; j++){
						int sx = i, sy = j, step = i-1+j-1;
						g[i][j] = n * m;
						for(int k=1; k<=(n*m)/d; k++){
							if(map[sx][sy] == 1){
								g[i][j] = min(g[i][j], step);
								break;
							}
							sx += dx, sy += dy;
							if(sx > n) sx -= n;
							if(sy > m) sy -= m;
							step = step + d;
						}
					}
				}
				
//				printf("\n");
//				for (int i=1;i<=dx+1;i++){
//					for (int j=1;j<=dy+1;j++){
//						printf("%lld ", g[i][j]);
//					}
//					printf("\n");
//				}
				
				memset(f, 0, sizeof(f));
				f[1][1][g[1][1]] = 1;
				for(int i=1; i<=dx+1; i++){
					for(int j=1; j<=dy+1; j++){
						for(int k=1; k<=n*m; k++){
							if(i+1 <= dx+1) f[i+1][j][min(k,g[i+1][j])] = (f[i+1][j][min(k,g[i+1][j])] + f[i][j][k]) % Mod;
							if(j+1 <= dy+1) f[i][j+1][min(k,g[i][j+1])] = (f[i][j+1][min(k,g[i][j+1])] + f[i][j][k]) % Mod;
						}
					}
				}
				for(int i=1; i<=n*m; i++)
					ans = (ans + f[dx+1][dy+1][i] * i) % Mod;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}