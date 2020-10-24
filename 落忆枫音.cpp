#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
#define fake false
using namespace std;
const int MaxN = 100005, Mod = 1000000007;
int n, m, x, y, ans, cnt, head[MaxN], cntEdge, degree[MaxN], f[MaxN];
bool visited[MaxN];
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
	degree[u]++;
	return;
}

inline int QuickPower(int a, int b){
	int res = 1;
	while(b){
		if(b & 1) res = res * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return res;
}

inline void DFS(int u){
	if(u == y) return;
	if(visited[u]) return;
	visited[u] = !fake;
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		DFS(v);
		f[u] = (f[u] + (f[v] * QuickPower(degree[u], Mod-2) % Mod) % Mod) % Mod;
	}
	return;
}

signed main(){
	n = Read(), m = Read(), x = Read(), y = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(v, u);
	}
	ans = cnt = degree[1] = 1;
	for(int i=1; i<=n; i++){
		ans = (ans * degree[i]) % Mod;
		if(i == y) cnt = cnt * (degree[i]+1) % Mod;
		else cnt = cnt * degree[i] % Mod;
	}
	f[y] = (f[y] + (ans * QuickPower(degree[y], Mod-2)) % Mod) % Mod;
	DFS(x);
	cnt = (cnt - f[x] + Mod) % Mod;
	if(y == 1 || x == y) printf("%lld", ans);
	else printf("%lld", cnt);
	return 0;
}