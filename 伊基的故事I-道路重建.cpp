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
const int MaxN = 505, MaxM = (50005 + MaxN) * 2;
int n, m, s, t, head[MaxN], cntEdge;
int dep[MaxN], cur[MaxN];
bool vs[MaxN], vt[MaxN];
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

inline void Find(int x, bool vis[], bool rev){
	vis[x] = true;
	for(int i = head[x]; ~i; i = edge[i].nextEdge){
		int j = i^rev, y = edge[i].destination;
		if(edge[j].capacity && !vis[y]) Find(y, vis, rev);
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	s = 0, t = n-1;
	memset(head, -1, sizeof(head));
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), c = Read();
		AddBranch(u, v, c);
	}
	Dinic();
//	printf("%d", Dinic());
	Find(s, vs, false);
	Find(t, vt, true);
	int ans = 0;
	for(int i=0; i<=(m-1)*2; i+=2){
		if(!edge[i].capacity && vs[edge[i^1].destination] && vt[edge[i].destination]) ans++;
	}
	printf("%d", ans);
	return 0;
}