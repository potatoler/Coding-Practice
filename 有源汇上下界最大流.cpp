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
const int MaxN = 205, MaxM = (MaxN + 10005) * 2;
int n, m, s, t, vs, vt, head[MaxN], cntEdge = -1, dc[MaxN];
queue<int> q;
int dep[MaxN], cur[MaxN];
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

inline void AddBranch(int u, int v, int w){
	cntEdge++;
	edge[cntEdge] = {v, head[u], w};
	head[u] = cntEdge;
	cntEdge++;
	edge[cntEdge] = {u, head[v], 0};
	head[v] = cntEdge;
	return;
}

inline bool BFS(){
	memset(dep, -1, sizeof(dep));
	while(q.size())
		q.pop();
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
		while(flow = DFS(vs, INT_MAX)) res += flow;
	}
	return res;
}

signed main(){
	memset(head, -1, sizeof(head));
	n = Read(), m = Read(), s = Read(), t = Read();
	vs = 0, vt = n+1;
	while(m--){
		int a = Read(), b = Read(), c = Read(), d = Read();
		AddBranch(a, b, d-c);
		dc[a] -= c;
		dc[b] += c;
	}
	int sum = 0;
	for(int i=1; i<=n; i++){
		if(dc[i] > 0) AddBranch(vs, i, dc[i]), sum += dc[i];
		else if(dc[i] < 0) AddBranch(i, vt, -dc[i]);
	}
	AddBranch(t, s, INT_MAX);
	if(Dinic() != sum) printf("No Solution");
	else{
		int res = edge[cntEdge].capacity;
		vs = s, vt = t;
		edge[cntEdge].capacity = edge[cntEdge-1].capacity = 0;
		printf("%d\n", res + Dinic());
	}
}