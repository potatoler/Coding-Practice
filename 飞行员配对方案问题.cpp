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
const int MaxN = 105;
int n, m, s, t, head[MaxN], cntEdge = -1;
int dep[MaxN], cur[MaxN];
struct Edge{
	int destination, nextEdge, capacity;
}edge[(MaxN*MaxN+MaxN*2)*2];

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
				dep[y] = dep[x]+1;
				cur[y] = head[y];
				if(y == t) return true;
				q.push(y);
			}
		}
	}
	return false;
}

inline int DFS(int x, int limit){
	if(x == t) return limit;
	int flow = 0;
	for(int i = cur[x]; ~i && flow < limit; i = edge[i].nextEdge){
		int y = edge[i].destination;
		cur[x] = i;
		if(dep[y] == dep[x]+1 && edge[i].capacity){
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
	while(BFS()){
		while(flow = DFS(s, INT_MAX)) res += flow;
	}
	return res;
}

signed main(){
	m = Read(), n = Read();
	s = 0, t = n+1;
	memset(head, -1, sizeof(head));
	while(true){
		int u = Read(), v = Read();
		if(u == -1 && v == -1) break;
		AddEdge(u, v, 1);
		AddEdge(v, u, 0);
	}
	for(int i=1; i<=m; i++){
		AddEdge(s, i, 1);
		AddEdge(i, s, 0);
	}
	for(int i=m+1; i<=n; i++){
		AddEdge(i, t, 1);
		AddEdge(t, i, 0);
	}
//	for(int x=1; x<=n; x++){
//		for(int i = head[x]; ~i; i = edge[i].nextEdge)
//			printf("%d ", edge[i].destination);
//		printf("\n");
//	}
	printf("%d\n", Dinic());
	for(int x=1; x<=m; x++){
		for(int i = head[x]; ~i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(y>m && y<=n && !edge[i].capacity){
				printf("%d %d\n", x, y);
			}
		}
	}
	return 0;
}