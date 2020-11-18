#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, q, lim, a[MaxN], head[MaxN], cntEdge;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
int f[MaxN], g[MaxN], ans[MaxN], s[MaxN][2];

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

inline void DFS1(int x, int fa){
	f[x] = g[x] = s[x][0] = s[x][1] = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		DFS1(y,x);
		if(a[y] > lim) continue;
		if(f[y] + a[y] > f[x]){
			g[x] = f[x];
			f[x] = f[y] + a[y];
			s[x][1] = s[x][0];
			s[x][0] = y;
		}
		else if(f[y] + a[y] > g[x]){
			g[x] = f[y] + a[y];
			s[x][1] = y;
		}
	}
	return;
}

inline void DFS2(int x, int fa){
	int tmp = s[fa][0] == x? g[fa] : f[fa];
	if(a[fa] <= lim){
		if(tmp + a[fa] > f[x]){
			g[x] = f[x];
			f[x] = tmp + a[fa];
			s[x][1] = s[x][0];
			s[x][0] = fa;
		}
		else if(tmp + a[fa] > g[x]){
			g[x] = tmp + a[fa];
			s[x][1] = fa;
		}
	}
	if(a[x] <= lim && f[x] + g[x] + a[x] > 0) ans[x] = f[x] + g[x] + a[x];
	else ans[x] = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		DFS2(y,x);
	}
	return;
}

signed main(){
	n = Read(), q = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	while(q--){
		lim = Read();
		DFS1(1,0);
		DFS2(1,0);
		for(int i=1; i<n; i++)
			printf("%lld ", ans[i]);
		printf("%lld\n", ans[n]);
	}
	return 0;
}