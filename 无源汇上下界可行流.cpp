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
const int MaxN = 202, MaxM = 10205;
int n, m, s, t, head[MaxN], cu[MaxM], cl[MaxM], cntEdge = -1, dc[MaxN], cur[MaxN], dep[MaxN];
struct Edge{
	int destination, nextEdge, capacity;
}edge[(MaxM+MaxN) * 2];

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

inline void AddBranch(int u, int v, int c){
	AddEdge(u, v, c);
	AddEdge(v, u, 0);
	return;
}

inline bool BFS(){
	memset(dep, -1, sizeof(dep));
	queue<int> q;
	q.push(s), cur[s] = head[s], dep[s] = 0;
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
	memset(head, -1, sizeof(head));
	n = Read(), m = Read();
	s = 0, t = n+1;
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		cl[i] = Read(), cu[i] = Read();
		AddBranch(u, v, cu[i] - cl[i]);
		dc[u] -= cl[i];
		dc[v] += cl[i];
	}
	int sum = 0;
	for(int i=1; i<=n; i++){
		if(dc[i] > 0) AddBranch(s, i, dc[i]), sum += dc[i];
		else if(dc[i] < 0) AddBranch(i, t, -dc[i]);
	}
	if(Dinic() != sum) printf("NO\n");
	else{
		printf("YES\n");
		for(int i=0; i<=(m-1)*2; i+=2)
			printf("%d\n", edge[i^1].capacity + cl[i/2+1]);
	}
	return 0;
}