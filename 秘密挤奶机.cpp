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
const int MaxN = 205, MaxM = 80008;
int n, m, s, t, T, head[MaxN], cntEdge;
int dep[MaxN], cur[MaxN];
queue<int> q;
struct Edge{
	int destination, nextEdge, value, capacity;
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
	edge[cntEdge] = {v, head[u], c, 0};
	head[u] = cntEdge++;
	edge[cntEdge] = {u, head[v], c, 0};
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

inline bool Check(int mid){
	for(int i=0; i<cntEdge; i++){
		if(edge[i].value > mid) edge[i].capacity = 0;
		else edge[i].capacity = 1;
	}
	return Dinic() >= T;
}

signed main(){
	n = Read(), m = Read(), T = Read();
	s = 1, t = n;
	memset(head, -1, sizeof(head));
	while(m--){
		int u = Read(), v = Read(), c = Read();
		AddBranch(u, v, c);
	}
	int l = 1, r = 1000000;
	while(l < r){
		int mid = (l+r) >> 1;
		if(Check(mid)) r = mid;
		else l = mid+1;
	}
	printf("%d", r);
	return 0;
}