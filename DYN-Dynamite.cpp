#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, m, head[MaxN], cntEdge, d[MaxN], f[MaxN], g[MaxN], ans, tot;
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

inline void DFS(int x, int fa, int mid){
	f[x] = -INT_MAX, g[x] = INT_MAX;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		DFS(y,x,mid);
		f[x] = max(f[x], f[y]+1);
		g[x] = min(g[x], g[y]+1);
	}
	if(f[x] + g[x] <= mid) f[x] = -INT_MAX;
	if(g[x] > mid && d[x] == 1) f[x] = max(f[x], 0ll);
	if(f[x] == mid){
		f[x] = -INT_MAX;
		g[x] = 0;
		tot++;
	}
	return;
}

inline bool Check(int x){
	tot = 0;
	DFS(1, 0, x);
	if(f[1] >= 0) tot++;
	return tot <= m;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		d[i] = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	int l = 0, r = n;
	while(l <= r){
		int mid = (l+r) >> 1;
		if(Check(mid)){
			r = mid - 1;
			ans = mid;
//			puts("True");
		}
		else{
			l = mid + 1;
//			puts("False");
		}
	}
	printf("%d", ans);
	return 0;
}