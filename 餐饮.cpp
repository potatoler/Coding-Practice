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
const int MaxN = 105 * 4, MaxM = MaxN*10;
int n, s, t, F, D;
int head[MaxN], cntEdge, dep[MaxN], cur[MaxN];
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM];
queue<int> q;

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

inline void AddBranch(int u, int v, int c){
	edge[cntEdge] = {v, head[u], c};
	head[u] = cntEdge++;
	edge[cntEdge] = {u, head[v], 0};
	head[v] = cntEdge++;
	return;
}

inline bool BFS(){
	while(q.size()) q.pop();
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
	if(x == t) return limit;
	int flow = 0;
	for(int i = cur[x]; ~i && flow < limit; i = edge[i].nextEdge){
		int y = edge[i].destination;
		cur[x] = i;
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
	while(BFS()){
		while(flow = DFS(s, INT_MAX)) res += flow;
	}
	return res;
}

signed main(){
	memset(head, -1, sizeof(head));
	n = Read(), F = Read(), D = Read();
	s = 0, t = n * 2 + F + D + 1;
	for(int i=1; i<=F; i++)
		AddBranch(s, n*2+i, 1);
	for(int i=1; i<=D; i++)
		AddBranch(n*2+F+i, t, 1);
	for(int i=1; i<=n; i++){
		AddBranch(i, n+i, 1);
		int f = Read(), d = Read();
		while(f--){
			int x = Read();
			AddBranch(n*2+x, i, 1);
		}
		while(d--){
			int x = Read();
			AddBranch(n+i, n*2+F+x, 1);
		}
	}
	printf("%d\n", Dinic());
	return 0;
}