#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 152;
int n, p, ans = INT_MAX, head[MaxN], degree[MaxN], cntEdge, f[MaxN][MaxN], subtreeSize[MaxN], father[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination

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
	father[v] = u;
	return;
}

inline void DP(int x){
	subtreeSize[x] = 1;
	if(!degree[x]){
		f[x][1] = 0;
		return;
	}
	for(int i = head[x]; i; i = edge[i].nextEdge){
		DP(thisSon);
		subtreeSize[x] += subtreeSize[thisSon];
		for(int j = subtreeSize[x]; j>=0; j--)
			for(int k=1; k<j; k++)
				f[x][j] = min(f[x][j], f[x][j-k] + f[thisSon][k] - 1);
	}
}

signed main(){
	n = Read(), p = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v);
	}
	memset(f, 0x3f, sizeof(f));
	for(int i=1; i<=n; i++)
		f[i][1] = degree[i];
	DP(1);
	for(int i=1; i<=n; i++){
		if(father[i]) f[i][p] += 1;
		ans = min(ans, f[i][p]);
//		printf("%lld %lld\n", father[i], f[i][p]);
	}
	printf("%lld", ans);
	return 0;
}