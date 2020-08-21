#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 505, MaxE = 50004;
int n, m, t;
int cntEdge, head[MaxN * 2];
int match[MaxN * 2], visitTime[MaxN * 2];
struct Edge{
	int destination, nextEdge;
}edge[MaxE];

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

inline bool DFS(int u, int tag){
	if(visitTime[u] == tag) return false;
	visitTime[u] = tag;
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		if(match[v] == 0 || DFS(match[v], tag)){
			match[v] = u;
			return true;
		}
	}
	return false;
}

signed main(){
	n = Read(), m = Read(), t = Read();
	for(int i=1; i<=t; i++){
		int u = Read(), v = Read();
		AddEdge(u, v);
	}
	int ans = 0;
	for(int i=1; i<=n; i++)
		if(DFS(i,i)) ans++;
	printf("%lld", ans);
}