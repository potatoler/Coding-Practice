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
const int MaxN = 505, MaxM = (MaxN*2 + 3000) * 2;
int n, m, k, s, t, head[MaxN], cntEdge, dep[MaxN], cur[MaxN], id[MaxN];
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM];
queue<int> q;
pair<int,int> graph[MaxM];

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

inline void AddBranch(int u, int v, int c1, int c2){
	edge[cntEdge] = {v, head[u], c1};
	head[u] = cntEdge++;
	edge[cntEdge] = {u, head[v], c2};
	head[v] = cntEdge++;
	return;
}

inline bool BFS(){
	memset(dep, -1, sizeof(dep));
	while(q.size()) q.pop();
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
		cur[x] = i;
		int y = edge[i].destination;
		if(dep[y] == dep[x] + 1 && edge[i].capacity){
			int avi = DFS(y, min(edge[i].capacity, limit-flow));
			if(!avi) dep[y] = -1;
			edge[i].capacity -= avi;
			edge[i^1].capacity += avi;
			flow += avi;
		}
	}
	return flow;
}

inline long long Dinic(int d){
	cntEdge = 0;
	memset(head, -1, sizeof(head));
	for(int i=0; i<m; i++){
		int u = graph[i].first, v = graph[i].second;
		AddBranch(u, v, 1, 1);
	}
	for(int i=1; i<=n; i++){
		if(id[i] >= 0){
			if(id[i] >> d & 1) AddBranch(i, t, INT_MAX, 0);
			else AddBranch(s, i, INT_MAX, 0);
		}
	}
	int res = 0, flow = 0;
	while(BFS()){
		while(flow = DFS(s, INT_MAX)) res += flow;
	}
	return (long long)res;
}

signed main(){
	n = Read(), m = Read();
	s = 0, t = n+1;
	for(int i=0; i<m; i++){
		int u = Read(), v = Read();
		graph[i] = {u,v};
	}
	memset(id, -1, sizeof(id));
	k = Read();
	for(int i=1; i<=k; i++){
		int u = Read(), p = Read();
		id[u] = p;
	}
	long long res = 0;
	for(int i=0; i<31; i++)
		res += Dinic(i) << i;
	printf("%lld\n", res);
	return 0;
}