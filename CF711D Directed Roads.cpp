#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 1000000007;
int n, m, head[MaxN], depth[MaxN], visited[MaxN], ringSize, cntEdge, ans = 1;
struct Edge{
	int from, to, nextEdge;
}edge[MaxN * 2];

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
	edge[cntEdge].from = u;
	edge[cntEdge].to = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline int QuickPower(int x, int y){
	int res = 1;
	while(y){
		if(y&1) res = res * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return res;
}

inline void FindRing(int x, int d){
	depth[x] = d, visited[x] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].to;
		if(!visited[y]) FindRing(y,d+1);
		else if(visited[y] == 1){
			ringSize = depth[x] - depth[y] + 1;
			ans = (ans * (QuickPower(2, ringSize) - 2 + Mod))% Mod;
			m -= ringSize;
		}
	}
	visited[x] = 2;
}

signed main(){
	m = n = Read();
	for(int i=1; i<=n; i++){
		int a = Read();
		AddEdge(i, a);
	}
	for(int i=1; i<=n; i++)
		if(!visited[i]){
			ringSize = 0;
			FindRing(i,0);
		}
	ans = ans * QuickPower(2, m) % Mod;
	printf("%lld\n", ans);
	return 0;
}