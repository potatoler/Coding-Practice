#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
const int MaxN = 205, MaxM = 5005;
int n, m, s, t;
int depth[MaxN], head[MaxN], cntEdge = 0;
long long maxFlow;
bool inqueue[MaxN];
struct Edge{
	int to, val, nextEdge;
}edge[MaxM*2];

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].to = v;
	edge[cntEdge].val = w;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
}

inline bool BFS(){
	memset(depth, 0x3f3f3f3f, sizeof(depth));
	memset(inqueue, false, sizeof(inqueue));
	depth[s] = 0;
	queue<int> q;
	q.push(s);
	while(q.size()){
		int u = q.front();
		q.pop();
		inqueue[u] = false;
		for(int i=head[u]; i; i=edge[i].nextEdge){
			int v = edge[i].to;
			if(depth[v] > depth[u]+1 && edge[i].val){
				depth[v] = depth[u] + 1;
				if(!inqueue[v]) q.push(v);
				inqueue[v] = true;
			}
		}
	}
	if(depth[t] != 0x3f3f3f3f) return 1;
	return 0;
}

inline int DFS(int cur, int flow){
	int delta = 0;
	if(cur == t) return flow;
	for(int i=head[cur]; i; i=edge[i].nextEdge){
		int v = edge[i].to;
		if(edge[i].val && depth[v] == depth[cur]+1){
			if(delta = DFS(v, min(flow, edge[i].val))){
				edge[i].val -= delta;
				edge[i^1].val += delta;
				return delta;
			}
		}
	}
	return 0;
}

long long Dinic(){
	long long low;
	while(BFS()){
		while(low = DFS(s, INT_MAX))
			maxFlow += low;
	}
	return maxFlow;
}

int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(u, v, w);
		AddEdge(v, u, 0); //反向边边权建成 0 啊！
	}
	printf("%lld",Dinic());
	return 0;
}