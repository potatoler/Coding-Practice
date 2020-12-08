#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 500005, Mod = 1000000007;
int n, k, w[15];
int c[MaxN], d[MaxN], ans;
int f[102][15][15][15][15][15];

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

inline int DFS(int dr, int cnt, int a1=1, int a2=1, int a3=1, int a4=1, int a5=1){
	if(a1 == 0 || a1 == w[1]+1 || a2 == 0 || a2 == w[2]+1 || a3 == 0 || a3 == w[3]+1 || a4 == 0 || a4 == w[4]+1 || a5 == 0 || a5 == w[5]+1) return f[cnt][a1][a2][a3][a4][a5] = 0;
	if(f[cnt][a1][a2][a3][a4][a5]) return f[cnt][a1][a2][a3][a4][a5];
	switch(c[cnt]){
		case 1:{
			int nxt = cnt+1;
			if(nxt == n+1) nxt = 1;
			return f[cnt][a1][a2][a3][a4][a5] = (f[cnt][a1][a2][a3][a4][a5] + DFS(nxt, a1+d[cnt], a2, a3, a4, a5)) % Mod;
			break;
		}
		case 2:{
			int nxt = cnt+1;
			if(nxt == n+1) nxt = 1;
			return f[cnt][a1][a2][a3][a4][a5] = (f[cnt][a1][a2][a3][a4][a5] + DFS(nxt, a1, a2+d[cnt], a3, a4, a5)) % Mod;
			break;
			break;
		}
		case 3:{
			int nxt = cnt+1;
			if(nxt == n+1) nxt = 1;
			return f[cnt][a1][a2][a3][a4][a5] = (f[cnt][a1][a2][a3][a4][a5] + DFS(nxt, a1, a2, a3+d[cnt], a4, a5)) % Mod;
			break;
			break;
		}
		case 4:{
			int nxt = cnt+1;
			if(nxt == n+1) nxt = 1;
			return f[cnt][a1][a2][a3][a4][a5] = (f[cnt][a1][a2][a3][a4][a5] + DFS(nxt, a1, a2, a3, a4+d[cnt], a5)) % Mod;
			break;
			break;
		}
		case 5:{
			int nxt = cnt+1;
			if(nxt == n+1) nxt = 1;
			return f[cnt][a1][a2][a3][a4][a5] = (f[cnt][a1][a2][a3][a4][a5] + DFS(nxt, a1, a2, a3, a4+d[cnt], a5)) % Mod;
			break;
			break;
		}
	}
}

signed main(){
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		c[i] = Read(), d[i] = Read();
	}
	for(int i=1; i<=k; i++)
		w[i] = Read();
	for(int i=k+1; i<=5; i++)
		w[i] = 1;
	for(int a1=w[1]; a1>=1; a1--){
		for(int a2=w[2]; a2>=1; a2--){
			for(int a3=w[3]; a3>=1; a3--){
				for(int a4=w[4]; a4>=1; a4--){
					for(int a5=w[5]; a5>=1; a5--){
						ans += DFS(1, a1, a2, a3, a4, a5);
						ans %= Mod;
					}
				}
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
