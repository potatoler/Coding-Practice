#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 998244353;
int n, p, colour[MaxN], f[MaxN][2][2][2], power2[MaxN], ans;

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

inline void Init(){
	power2[0] = 1;
	for(int i=1; i<=n; i++){
		power2[i] = power2[i-1] << 1;
		if(power2[i] > Mod) power2[i] -= Mod;
	}
	return;
}

signed main(){
	n = Read(), p = Read();
	Init();
	for(int i=1; i<=n; i++){
		colour[i] = Read();
		// 0 for white, 1 for black, and -1 for unsure
	}
	f[0][0][0][0] = 1;
	for(int i=0; i<n; i++){
		for(int j=0; j<=1; j++){
			for(int x=0; x<=1; x++){
				for(int y=0; y<=1; y++){
					if(colour[i+1] == 0 || colour[i+1] == -1){
						if(x == 0) f[i+1][j^1][x][1] = (f[i+1][j^1][x][1] + power2[i] * f[i][j][x][y]) % Mod;
						else{
							f[i+1][j^1][x][1] = (f[i+1][j^1][x][1] + power2[i-1] * f[i][j][x][y]) % Mod;
							f[i+1][j][x][y] = (f[i+1][j][x][y] + power2[i-1] * f[i][j][x][y]) % Mod;
						}
					}
					if(colour[i+1] == 1 || colour[i+1] == -1){
						if(y == 0) f[i+1][j^1][1][y] = (f[i+1][j^1][1][y] + power2[i] * f[i][j][x][y]) % Mod;
						else{
							f[i+1][j^1][1][y] = (f[i+1][j^1][1][y] + power2[i-1] * f[i][j][x][y]) % Mod;
							f[i+1][j][x][y] = (f[i+1][j][x][y] + power2[i-1] * f[i][j][x][y]) % Mod;
						}
					}
				}
			}
		}
	}
	ans = (f[n][p][0][0] + f[n][p][0][1] + f[n][p][1][0] + f[n][p][1][1]) % Mod;
	printf("%lld", ans);
	return 0;
}