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
const int MaxN = 10004, MaxM = 100005;
int n, m, s, t, head[MaxN], cntEdge = -1;
queue<int> q;
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM*2];
int dep[MaxN], cur[MaxN];

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
	memset(dep, -1, sizeof(dep));
	while(q.size())
		q.pop();
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
	if(x == t) return limit;
	int flow = 0;
	for(int i = cur[x]; ~i && flow < limit; i = edge[i].nextEdge){
		int y = edge[i].destination;
		cur[x] = i;
		if(dep[y] == dep[x]+1 && edge[i].capacity){
			int avi = DFS(y, min(edge[i].capacity, limit-flow));
			if(!avi) dep[y] = -1;
			edge[i].capacity -= avi;
			edge[i^1].capacity += avi;
			flow += avi;
		}
	}
	return flow;
}

inline int Dinic(){
	int res = 0, flow;
	while(BFS()){
		while(flow = DFS(s, INT_MAX)){
			res += flow;
		}
	}
	return res;
}

signed main(){
	n = Read(), m = Read(), s = Read(), t = Read();
	memset(head, -1, sizeof(head)); // important
	while(m--){
		int u = Read(), v = Read(), c = Read();
		AddEdge(u, v, c);
		AddEdge(v, u, 0);
	}
//	for(int x=1; x<=n; x++){
//		for(int i = head[x]; ~i; i = edge[i].nextEdge)
//			printf("%d ", edge[i].destination);
//		printf("\n");
//	}
	printf("%d", Dinic());
	return 0;
}