#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 202 * 2, MaxM = 20004 * 2;
int n, m, s, t, cntEdge = 1, dist[MaxN], pre[MaxN], head[MaxN], lastEdge[MaxN], lastVertex[MaxN], minFlow[MaxN], maxFlow, minCost;
bool visited[MaxN];
struct Edge{
	int destination, nextEdge, cost, flow;
}edge[MaxM * 2];

inline int Read(){
	int num = 0, op = 1;
	char ch=  getchar();
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

inline void AddEdge(int u, int v, int c, int f){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].cost = c;
	edge[cntEdge].flow = f;
	head[u] = cntEdge;
}

inline bool SPFA(int s, int t){
	for(int i=s; i<=t; i++)
		dist[i] = INT_MAX;
	memset(visited, false, sizeof(visited));
	memset(minFlow, -1, sizeof(minFlow));
	memset(lastVertex, -1, sizeof(lastVertex));
	memset(lastEdge, -1, sizeof(lastEdge));
	queue<int> q;
	dist[s] = 0, minFlow[s] = INT_MAX;
	q.push(s);
	while(q.size()){
		int u = q.front();
		q.pop();
		visited[u] = false;
		for(int i = head[u]; i; i = edge[i].nextEdge){
			int v = edge[i].destination;
			if(!edge[i].flow) continue;
			if(dist[v] > dist[u] + edge[i].cost){
				dist[v] = dist[u] + edge[i].cost;
				lastEdge[v] = i, lastVertex[v] = u;
				minFlow[v] = min(minFlow[u], edge[i].flow);
				if(!visited[v]) visited[v] = true, q.push(v);
			}
		}
	}
	return (dist[t] != INT_MAX);
}


inline void MCMF(int s, int t){
	while(SPFA(s,t)){
		maxFlow += minFlow[t];
		minCost += minFlow[t] * dist[t];
		int x = t;
		while(x != s){
			edge[lastEdge[x]].flow -= minFlow[t];
			edge[lastEdge[x]^1].flow += minFlow[t];
			x = lastVertex[x];
		}
	}
}

signed main(){
	n = Read(), m = Read();
	s = 1, t = n*2;
	AddEdge(1, 1+n, 0, INT_MAX), AddEdge(1+n, 1, 0, -INT_MAX);
	AddEdge(n, n+n, 0, INT_MAX), AddEdge(n+n, n, 0, -INT_MAX);
	for(int i=2; i<n; i++)
		AddEdge(i, i+n, 0, 1), AddEdge(i+n, i, 0, 0);
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), c = Read();
		AddEdge(u+n, v, c, 1), AddEdge(v, u+n, -c, 0);
	}
	MCMF(s, t);
	printf("%lld %lld\n", maxFlow, minCost);
	return 0;
}