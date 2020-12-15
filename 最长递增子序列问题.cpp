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
const int MaxN = 1005, MaxM = 250005 + MaxN;
int n, s, t, head[MaxN], cntEdge, f[MaxN], w[MaxN];
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM];
int cur[MaxN], dep[MaxN];
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
	int res = 0, flow = 0;
	while(BFS()){
		while(flow = DFS(s, INT_MAX)) res += flow;
	}
	return res;
}

signed main(){
	memset(head, -1, sizeof(head));
	n = Read();
	s = 0, t = n*2+1;
	for(int i=1; i<=n; i++)
		w[i] = Read();
	int mx = 0;
	for(int i=1; i<=n; i++){
		f[i] = 1;
		AddBranch(i, n+i, 1);
		for(int j=1; j<i; j++)
			if(w[j] <= w[i]) f[i] = max(f[i], f[j] + 1);
		for(int j=1; j<i; j++)
			if(w[j] <= w[i] && f[j]+1 == f[i]) AddBranch(n+j, i, 1);
		mx = max(mx, f[i]);
		if(f[i] == 1) AddBranch(s, i, 1);
	}
	for(int i=1; i<=n; i++)
		if(f[i] == mx) AddBranch(n+i, t, 1);
	printf("%d\n", mx);
	if(mx == 1) printf("%d\n%d\n", n, n);
	else{
		int res = Dinic();
		printf("%d\n", res);
		for(int i=0; i<cntEdge; i+=2){
			int u = edge[i^1].destination, v = edge[i].destination;
			if(u == s && v == 1) edge[i].capacity = INT_MAX;
			else if(u == 1 && v == n+1) edge[i].capacity = INT_MAX;
			else if(u == n && v == n+n) edge[i].capacity = INT_MAX;
			else if(u == n+n && v == t) edge[i].capacity = INT_MAX;
		}
		printf("%d\n", res + Dinic());
	}
}