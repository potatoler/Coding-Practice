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
const int MaxN = 105, MaxM = 400 * 4;
const double eps = 1e-8;
int n, m, s, t, head[MaxN], cntEdge, dep[MaxN], cur[MaxN];
struct Edge{
	int destination, nextEdge, value;
	double capacity;
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

inline void AddBranch(int u, int v, int w){
	edge[cntEdge] = {v, head[u], w};
	head[u] = cntEdge++;
	edge[cntEdge] = {u, head[v], w};
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
			if(dep[y] == -1 && edge[i].capacity > eps){
				dep[y] = dep[x] + 1;
				cur[y] = head[y];
				if(y == t) return true;
				q.push(y);
			}
		}
	}
	return false;
}

inline double DFS(int x, double limit){
	if(x == t) return limit;
	double flow = 0;
	for(int i = cur[x]; ~i && limit - flow > eps; i = edge[i].nextEdge){
		int y = edge[i].destination;
		cur[x] = i;
		if(dep[y] == dep[x] + 1 && edge[i].capacity > eps){
			double avi = DFS(y, min(edge[i].capacity, limit-flow));
			if(avi < eps) dep[y] = -1;
			edge[i].capacity -= avi;
			edge[i^1].capacity += avi;
			flow += avi;
		}
	}
	return flow;
}

double Dinic(double mid){
	double tmp = 0;
	for(int i=0; i<cntEdge; i+=2){
		if(edge[i].value <= mid){
			tmp += edge[i].value - mid;
			edge[i].capacity = edge[i^1].capacity = 0;
		}
		else edge[i].capacity = edge[i^1].capacity = edge[i].value-mid;
	}
	double res = 0, flow;
	while(BFS()){
		while(flow = DFS(s, 1e8)) res += flow;
	}
//	printf("%.2lf ", res + tmp);
	return res + tmp;
}

signed main(){
	memset(head, -1, sizeof(head));
	n = Read(), m = Read(), s = Read(), t = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddBranch(u, v, w);
	}
	double l=0, r = 10000000;
	while(r-l > eps){
		double mid = (l+r) / 2;
		if(Dinic(mid) < 0) r = mid;
		else l = mid;
	}
	printf("%.2f\n", r);
	return 0;
}