#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2003;
int n, m, head[MaxN], cntEdge;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*2];
int f[MaxN][MaxN], size[MaxN], g[MaxN];

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

inline void DP(int x, int father){
	size[x] = 1;
	for(int k = head[x]; k; k = edge[k].nextEdge){
		int y = edge[k].destination;
		if(y == father) continue;
		DP(y, x);
//		memset(g, 0, sizeof(g));
		for(int i=0; i<=m; i++)
			g[i] = 0;
		for(int i=0; i<=size[x]; i++){
			for(int j=0; j<=size[y]; j++){
				if(i + j <= m){
					int w = j * (m-j) + (size[y]-j) * (n - m - (size[y]-j));
					g[i+j] = max(g[i+j], f[x][i] + f[y][j] + w * edge[k].value);
				}
			}
		}
//		memcpy(f[x], g, sizeof(g));
		for(int i=0; i<=m; i++)
			f[x][i] = g[i];
		size[x] += size[y];
	}
}

signed main(){
//	freopen("coloration.in", "r", stdin);
//	freopen("coloration.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	DP(1,0);
	printf("%lld", f[1][m]);
}