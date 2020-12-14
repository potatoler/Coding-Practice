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
const int MaxN = 10010, MaxM = (100005 + MaxN) * 2;
int n, m, vs, vt, sc, tc, head[MaxN], cntEdge;
int dep[MaxN], cur[MaxN];
queue<int> q;
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM];

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
	q.push(vs), dep[vs] = 0, cur[vs] = head[vs];
	while(q.size()){
		int x = q.front();
		q.pop();
		for(int i = head[x]; ~i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(dep[y] == -1 && edge[i].capacity){
				dep[y] = dep[x] + 1;
				cur[y] = head[y];
				if(y == vt) return true;
				q.push(y);
			}
		}
	}
	return false;
}

inline int DFS(int x, int limit){
	if(x == vt) return limit;
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
	while(BFS()){
		while(flow = DFS(vs, INT_MAX)) res += flow;
	}
	return res;
}

signed main(){
	memset(head, -1, sizeof(head));
	n = Read(), m = Read(), sc = Read(), tc = Read();
	vs = 0, vt = n+1;
	while(sc--){
		int s = Read();
		AddBranch(vs, s, INT_MAX);
	}
	while(tc--){
		int t = Read();
		AddBranch(t, vt, INT_MAX);
	}
	while(m--){
		int u = Read(), v = Read(), c = Read();
		AddBranch(u, v, c);
	}
	printf("%d", Dinic());
	return 0;
}