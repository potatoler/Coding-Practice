#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
const int MaxN = 300;
int n, m, s, t;
int r[MaxN], c[MaxN], head[MaxN*2], cntEdge = -1;
int dep[MaxN*2], cur[MaxN*2];
struct Edge{
	int destination, nextEdge, capacity;
}edge[(MaxN*MaxN+MaxN*2) * 2];

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

inline void AddEdge(int u, int v, int c){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].capacity = c;
	head[u] = cntEdge;
	return;
}

inline bool BFS(){
	queue<int> q;
	memset(dep, -1, sizeof(dep));
	q.push(s), dep[s] = 0, cur[s] = head[s];
	while(q.size()){
		int x = q.front();
		q.pop();
		for(int i = head[x]; ~i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(dep[y] == -1 && edge[i].capacity){
				dep[y] = dep[x] + 1;
				cur[y] = head[y];
				if(y == t) return true;
				q.push(y);
			}
		}
	}
	return false;
}

inline int DFS(int x, int limit){
	if(x == t || !limit) return limit;
	int flow = 0;
	for(int i = cur[x]; ~i && flow < limit; i = edge[i].nextEdge){
		cur[x] = i;
		int y = edge[i].destination;
		if(dep[y] == dep[x] + 1 && edge[i].capacity){
			int avi = DFS(y, min(edge[i].capacity, limit - flow));
			if(!avi) dep[y] = -1;
			edge[i].capacity -= avi;
			edge[i^1].capacity += avi;
			flow += avi;
		}
	}
	return flow;
}

inline int Dinic(){
	int res = 0, flow = 0;
	while(BFS())
		while(flow = DFS(s, INT_MAX)) res += flow;
	return res;
}

signed main(){
//	freopen("table.in", "r", stdin);
//	freopen("table.out", "w", stdout);
	memset(head, -1, sizeof(head));
	m = Read(), n = Read();
	s = 0, t = n+m+1;
	int sum = 0;
	for(int i=1; i<=m; i++){
		r[i] = Read(), sum += r[i];
		AddEdge(s, i, r[i]);
		AddEdge(i, s, 0);
	}
	for(int i=1; i<=n; i++){
		c[i] = Read();
		AddEdge(m+i, t, c[i]);
		AddEdge(t, m+i, 0);
	}
	for(int i=1; i<=m; i++){
		for(int j=m+1; j<=m+n; j++){
			AddEdge(i, j, 1);
			AddEdge(j, i, 0);
		}
	}
	if(Dinic() != sum){
		printf("0");
		return 0;
	}
	printf("1\n");
	for(int x = 1; x<=m; x++){
		for(int i = head[x]; ~i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(!edge[i].capacity && y>m && y<=m+n) printf("%d ", y-m);
		}
		puts("");
	}
	return 0;
}