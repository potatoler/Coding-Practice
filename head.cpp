#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 998244353, half = (Mod+1) / 2;
int n, head[MaxN], cntEdge;
int siz[MaxN], g[MaxN], f[MaxN], ans;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline int QuickPower(int x, int y){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return res;
}

inline int Pow(int x){
	if(x == 0) return 1;
	return QuickPower(2, x * (x + 1) / 2 % (Mod-1));
}

inline int Inv(int x){
	if(x == 0) return 1;
	return QuickPower(half, x * (x + 1) / 2 % (Mod-1));
}

inline void DFS1(int x, int father){
	f[x] = g[x] = siz[x] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == father) continue;
		DFS1(y, x);
		siz[x] += siz[y];
		f[x] = f[x] * ((f[y] + (Pow(siz[y]) - g[y] + Mod) % Mod) % Mod) % Mod;
		g[x] = g[x] * Pow(siz[y]) % Mod;
	}
}

inline void DFS2(int x, int father){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == father) continue;
		int h = g[x] * Inv(siz[y]) % Mod * Pow(n-siz[x]) % Mod;
		ans = (ans + (f[y] * ((Pow(n-siz[y]) - h + Mod) % Mod) % Mod)) % Mod;
		DFS2(y, x);
	}
}

signed main(){
	n = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v);
		AddEdge(v,u);
	}
	DFS1(1,0);
//	for(int i=1; i<=n; i++)
//		printf("%lld %lld\n", f[i], g[i]);
	DFS2(1,0);
	ans = (ans + f[1]) % Mod;
	printf("%lld", ans);
	return 0;;
}