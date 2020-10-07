#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
const int MaxN = 300005, MaxM = 500005, Mod = 998244353;
int n, m, head[MaxN], cntEdge, depth[MaxN], ans=1, sum;
struct Edge{
	int destination, nextEdge;
}edge[MaxM*2];

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
	int ans = 1;
	while(y > 0){
		if(y&1) ans = ans * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return ans;
}

inline void DFS(int x, int fa){
	depth[x] = depth[fa] + 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		if(!depth[y]) DFS(y, x);
		else if(depth[x] > depth[y]){
			int tmp = depth[x]- depth[y] + 1;
			sum += tmp;
			ans = ans * (QuickPower(2, tmp)-1) % Mod;
		}
	}
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	for(int i=1; i<=n; i++)
		if(!depth[i]) DFS(i, 0);
	ans = ans * QuickPower(2, m-sum) % Mod;
	printf("%lld", ans);
	return 0;
}