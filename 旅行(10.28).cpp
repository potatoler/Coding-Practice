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
int n, m, q, head[MaxN], cntEdge, a[MaxN], d[MaxN], f[MaxN], g[MaxN], h[MaxN];
int stack[MaxN], top;
int fg[MaxN], fh[MaxN], e[MaxN];
int queue[MaxN], cnt, value[MaxN];
struct Edge{
	int destination, nextEdge, value;
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

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void DFS1(int x, int father){
	f[x] = a[x];
	if(top > d[x]) f[stack[top-d[x]]] = (f[stack[top-d[x]]] - a[x] + Mod) % Mod;
	stack[++top] = x;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == father) continue;
		DFS1(y, x);
		f[x] = (f[x] + f[y]) % Mod;
	}
	stack[top--] = 0;
	return;
}

inline void DFS2(int x, int father){
	g[x] = f[x] * f[x] % Mod;
	h[x] = f[x];
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination, z = edge[i].value;
		if(y == father) continue;
		DFS2(y, x);
		g[x] = (g[x] + z * (g[y] + 2 * h[y] * h[x] % Mod) % Mod) % Mod;
		h[x] = (h[x] + z * h[y]) % Mod;
	}
	return;
}

inline void DP(int x, int father, int w){
	e[x] = (g[x] + w * (fg[x] + 2 * fh[x] * h[x] % Mod) % Mod) % Mod;
	int gg = (f[x] * f[x] % Mod + w * (fg[x] + 2 * fh[x] * f[x] % Mod) % Mod) % Mod;
	int hh = (fh[x] * w + f[x]) % Mod;
	cnt = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination, z = edge[i].value;
		if(y == father) continue;
		fg[y] = gg, fh[y] = hh;
		gg = (gg + z * (g[y] + 2 * hh * h[y] % Mod) % Mod) % Mod;
		hh = (hh + z * h[y]) % Mod;
		queue[++cnt] = y;
		value[cnt] = z;
	}
	gg = 0, hh = 0;
//	printf("%lld\n", cnt);
	for(int i = cnt; i>=1; i--){
		int y = queue[i];
		fg[y] = (fg[y] + gg + 2 * fh[y] * hh % Mod) % Mod;
		fh[y] = (fh[y] + hh) % Mod;
		gg = (gg + value[i] * (g[y] + 2 * hh * h[y] % Mod) % Mod) % Mod;
		hh = (hh + value[i] * h[y]) % Mod;
//		printf("%lld %lld %lld %lld\n", gg, hh, fg[y], fh[y]);
	}
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination, z = edge[i].value;
		if(y == father) continue;
		DP(y, x, z);
	}
	return;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read(), d[i] = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	DFS1(1, 0);
	DFS2(1, 0);
	DP(1, 0, 0);
//	for(int i=1; i<=n; i++){
//		printf("%lld %lld %lld %lld %lld\n", f[i], g[i], h[i], fg[i], fh[i]);
//	}
	q = Read();
	while(q--){
		int x = Read();
		printf("%lld\n", e[x]);
	}
	return 0;
}