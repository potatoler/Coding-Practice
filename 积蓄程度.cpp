#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 200005;
int T, n, cntEdge, head[MaxN], degree[MaxN], maxFlow[MaxN], subtreeFlow[MaxN], ans = -INT_MAX;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN * 2];
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

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	degree[u]++;
	return;
}

inline void DFS1(int x, int father){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		if(degree[thisSon] == 1) subtreeFlow[thisSon] = edge[i].value;
		DFS1(thisSon, x);
		subtreeFlow[x] += min(subtreeFlow[thisSon], edge[i].value);
	}
}

inline void DFS2(int x, int father){
	int tmp = 0;
	if(degree[x] == 1) tmp = edge[head[x]].value;
	else for(int i = head[x]; i; i = edge[i].nextEdge){
//		if(thisSon == father) continue;
		tmp += min(subtreeFlow[thisSon], edge[i].value);
	}
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		int rootFlow = subtreeFlow[x], sonFlow = subtreeFlow[thisSon];
		subtreeFlow[x] = tmp;
		if(degree[x] > 1) subtreeFlow[x] = subtreeFlow[x] - min(subtreeFlow[thisSon], edge[i].value);
		subtreeFlow[thisSon] = 0;
		for(int j = head[thisSon]; j; j = edge[j].nextEdge){
			subtreeFlow[thisSon] += min(subtreeFlow[edge[j].destination], edge[j].value);
		}
		maxFlow[thisSon] = subtreeFlow[thisSon];
		DFS2(thisSon, x);
	}
}

inline void Reset(){
	// Haruki, reset!
	memset(head, 0, sizeof(head));
	memset(subtreeFlow, 0, sizeof(subtreeFlow));
	memset(maxFlow, 0, sizeof(maxFlow));
	memset(degree, 0, sizeof(degree));
	cntEdge = 0;
	ans = -INT_MAX;
	// Reset.
}

signed main(){
	T = Read();
	while(T--){
		n = Read();
		Reset();
		for(int i=1; i<n; i++){
			int u = Read(), v = Read(), w = Read();
			AddEdge(u,v,w);
			AddEdge(v,u,w);
		}
		DFS1(1,0);
		maxFlow[1] = subtreeFlow[1];
		DFS2(1,0);
		for(int i=1; i<=n; i++)
			ans = max(ans, maxFlow[i]);
		printf("%lld\n", ans);
	}
	return 0;
}