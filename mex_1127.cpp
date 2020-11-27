#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 3003;
int n, head[MaxN], cntEdge, root, ans;
int f[MaxN][MaxN], father[MaxN][MaxN], siz[MaxN][MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

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

inline void DFS(int x, int fa){
	siz[root][x] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == fa) continue;
		father[root][y] = x;
		DFS(y,x);
		siz[root][x] += siz[root][y];
	}
	return;
}

inline int Calculate(int x, int y){
	if(x == y) return 0;
	if(f[x][y]) return f[x][y];
	return f[x][y] = max(Calculate(x,father[x][y]), Calculate(father[y][x],y)) + siz[x][y] * siz[y][x];
}

signed main(){
	n = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v), AddEdge(v,u);
	}
//	exit(0);
	for(int i=1; i<=n; i++){
		root = i;
		DFS(i, 0);
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			ans = max(ans, Calculate(i,j));
		}
	}
	printf("%lld", ans);
	return 0;
}