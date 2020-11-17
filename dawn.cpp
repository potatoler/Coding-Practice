#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 998244353, MaxK = 102;
int T, n, q;
int head[MaxN], cntEdge, father[MaxN][20], depth[MaxN];
int sz[MaxN][MaxK], sum[MaxN][MaxK], last[MaxN][MaxK];
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

inline void DFS(int x, int fa){
	depth[x] = depth[fa] + 1;
	father[x][0] = fa;
	for(int i=1; i<20; i++)
		father[x][i] = father[father[x][i-1]][i-1];
	sz[x][1] = 1;
	for(int i=1; i<MaxK; i++)
		sum[x][i] = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		DFS(y,x);
		sz[x][1] = (sz[x][1] + sz[y][1]) % Mod;
		for(int j=1; j<MaxK; j++)
			sum[x][j] = (sum[x][j] + sz[y][j]) % Mod;
	}
	for(int i=2; i<MaxK; i++)
		sz[x][i] = sz[x][i-1] * sz[x][1] % Mod;
	if(x == 1) last[x][1] = 0;
	else last[x][1] = n - sz[x][1];
	for(int i=2; i<MaxK; i++)
		last[x][i] = last[x][i-1] * last[x][1] % Mod;
}

inline int LCA(int x, int y){
	if(depth[x] < depth[y]) swap(x,y);
	for(int i=19; i>=0; i--)
		if(depth[father[x][i]] >= depth[y]) x = father[x][i];
	if(x == y) return x;
	for(int i=19; i>=0; i--)
		if(father[x][i] != father[y][i]){
			x = father[x][i];
			y = father[y][i];
		}
	return father[x][0];
}

inline int Calculate(int x, int y, int k){
	int ans = 0;
	ans = (ans + sz[x][k] * sz[y][k] % Mod) % Mod;
	ans = (ans - sum[x][k] * sz[y][k] % Mod + Mod) % Mod;
	ans = (ans - sz[x][k] * sum[y][k] % Mod + Mod) % Mod;
	ans = (ans + sum[x][k] * sum[y][k] % Mod) % Mod;
	return ans;
}

inline int Son(int x, int y){
	if(depth[x] < depth[y]) swap(x,y);
	for(int i=19; i>=0; i--)
		if(depth[father[x][i]] > depth[y]) x = father[x][i];
	return x;
}

inline int Special(int x, int y, int k){
	if(depth[x] > depth[y]) swap(x,y);
	int ans = 0, lca = Son(x,y);
	int tmp = (sum[x][k] - sz[lca][k] + last[x][k] + Mod) % Mod;
	ans = (ans + sz[y][k] * last[lca][k] % Mod) % Mod;
	ans = (ans - tmp * sz[y][k] % Mod + Mod) % Mod;
	ans = (ans - sum[y][k] * last[lca][k] % Mod + Mod) % Mod;
	ans = (ans + tmp * sum[y][k] % Mod) % Mod;
	return ans;
}

signed main(){
//	freopen("dawn.in", "r", stdin);
//	freopen("dawn.out", "w", stdout);
	T = Read();
	while(T--){
		n = Read(), q = Read();
		cntEdge = 0;
		memset(head, 0, sizeof(head));
		for(int i=1; i<n; i++){
			int u = Read(), v = Read();
			AddEdge(u,v), AddEdge(v,u);
		}
		DFS(1,0);
//		for(int i=1; i<=n; i++){
//			for(int j=1; j<20; j++){
//				printf("%lld %lld %lld %lld\n", father[i][j], sz[i][j], sum[i][j], last[i][j]);
//			}
//		}
		while(q--){
			int k = Read(), x = Read(), y = Read();
			int lca = LCA(x,y);
			if(lca == x || lca == y) printf("%lld\n", Special(x, y, k));
			else printf("%lld\n", Calculate(x, y, k));
		}
	}
	return 0;
}