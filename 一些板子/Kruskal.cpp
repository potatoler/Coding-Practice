#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 5003, MaxM = 200005;
int n, m, cntEdge, father[MaxN], ans, tot;
struct Edge{
	int u, v, w;
	inline bool operator < (const Edge &y) const {
		return w < y.w;
	}
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

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge] = (Edge){u,v,w};
	return;
}

inline int Find(int x){
	return father[x] == x ? x : father[x] = Find(father[x]);
}

inline void Kruskal(){
	sort(edge+1, edge+1+cntEdge);
	for(int i=1; i<=m; i++){
		int fu = Find(edge[i].u), fv = Find(edge[i].v);
		if(fu == fv) continue;
		ans += edge[i].w;
		father[fv] = fu;
		if(++tot == n-1) break;
	}
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		father[i] = i;
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
	}
	Kruskal();
	printf("%lld", ans);
	return 0;
}