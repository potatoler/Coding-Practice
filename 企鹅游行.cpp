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
const int MaxN = 205, MaxM = (MaxN*MaxN + MaxN*2) * 2;
int N, T, s, t, head[MaxN], cntEdge, cur[MaxN], dep[MaxN];
double D;
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM];
struct Ice{
	double x, y;
	int n, m;
}ice[MaxN];
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

inline bool Reachable(int i, int j){
	return sqrt((ice[j].x - ice[i].x) * (ice[j].x - ice[i].x) + (ice[j].y - ice[i].y) * (ice[j].y - ice[i].y)) <= D;
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
	T = Read();
	while(T--){
		s = 0;
		memset(head, -1, sizeof(head));
		scanf("%d%lf", &N, &D);
		cntEdge = 0;
		int sum = 0;
		for(int i=1; i<=N; i++){
			scanf("%lf%lf%d%d", &ice[i].x, &ice[i].y, &ice[i].n, &ice[i].m);
			sum += ice[i].n;
		}
		for(int i=1; i<=N; i++){
			AddBranch(s, i, ice[i].n);
			AddBranch(i, i+N, ice[i].m);
			for(int j=i+1; j<=N; j++){
				if(Reachable(i,j)){
					AddBranch(i+N, j, INT_MAX);
					AddBranch(j+N, i, INT_MAX);
				}
			}
		}
		int cnt = 0;
		for(int i=1; i<=N; i++){
			t = i;
			for(int j=0; j<cntEdge; j+=2){
				edge[j].capacity += edge[j^1].capacity;
				edge[j^1].capacity = 0;
			}
			if(Dinic() == sum) printf("%d ", i-1), cnt++;
		}
		if(!cnt) printf("-1");
		printf("\n");
	}
}