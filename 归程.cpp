#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 200005; // MaxM is MaxN*2.
int n, m, Q, K, S, head_on_Graph[MaxN], head_on_Tree[MaxN], cntEdge_Graph, cntEdge_Tree;
int dis[MaxN], fa[MaxN], mn[MaxN], graph[MaxN][25], val[MaxN], cntVal;
bool visited[MaxN];
struct GraphEdge{
	int from, destination, nextEdge, length, altitude;
}edge_graph[MaxN*4];
struct TreeEdge{
	int destinaiton, nextEdge, length;
}edge_tree[MaxN*4];
priority_queue< pair<int,int> > q;

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

inline void AddGraphEdge(int u, int v, int l, int a){
	edge_graph[++cntEdge_Graph] = (GraphEdge){u, v, head_on_Graph[u], l, a};
	head_on_Graph[u] = cntEdge_Graph;
}

inline void AddTreeEdge(int u, int v, int l){
	edge_tree[++cntEdge_Tree] = (TreeEdge){v, head_on_Tree[u], l};
	head_on_Tree[u] = cntEdge_Tree;
}

inline bool cmp(GraphEdge a, GraphEdge b){
	return a.altitude > b.altitude;
}

inline void Dijkstra(){// on tree
	memset(dis, 0x3f, sizeof(dis));
	memset(visited, false, sizeof(visited));
	dis[1] = 0;
	q.push(make_pair(0, 1));
	while(q.size()){
		int u = q.top().second;
		q.pop();
		if(visited[u]) continue;
		visited[u] = true;
		for(int i = head_on_Tree[u]; i; i = edge_tree[i].nextEdge){
			int v = edge_tree[i].destinaiton;
			if(dis[u] + edge_tree[i].length < dis[v]){
				dis[v] = dis[u] + edge_tree[i].length;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}

inline int Find(int x){
	if(fa[x] == x) return x;
	return fa[x] = Find(fa[x]);
}

inline void DFS(int u){
	mn[u] = dis[u];
	for(int i = head_on_Tree[u]; i; i = edge_tree[i].nextEdge){
		int v = edge_tree[i].destinaiton;
		graph[v][0] = u;
		DFS(v);
		mn[u] = min(mn[u], mn[v]);
	}
}

inline void Kruskal(){
	memset(head_on_Graph, 0, sizeof(head_on_Graph));
	sort(edge_graph+1, edge_graph+1+m, cmp);
	for(int i=1; i<=n; i++)
		fa[i] = i;
	for(int i=1; i<=m; i++){
		int fu = Find(edge_graph[i].from), fv = Find(edge_graph[i].destination);
		if(fu != fv){
			val[++cntVal] = edge_graph[i].altitude;
			fa[fu] = fa[fv] = fa[cntVal] = cntVal;
			AddTreeEdge(cntVal, fu, 0), AddTreeEdge(cntVal, fv, 0);
		}
	}
	DFS(cntVal);
}

inline void Reset(){// Haruki, reset!
	memset(head_on_Graph, 0, sizeof(head_on_Graph));
	memset(head_on_Tree, 0, sizeof(head_on_Tree));
	memset(graph, 0, sizeof(graph));
	memset(mn, 0x3f, sizeof(mn));
}

signed main(){
	int T=Read();
	while(T--){
		Reset();
		n=Read(), m=Read(), cntVal = n;
		for(int i=1; i<=m; i++){
			int u=Read(), v=Read(), l=Read(), a=Read();
			AddTreeEdge(u, v, l), AddTreeEdge(v, u, l);
			AddGraphEdge(u, v, l, a);
		}
		Dijkstra();
		Kruskal();		
		for(int i=1; (1<<i)<=cntVal; i++)
			for(int u=1; u<=cntVal; u++)
				graph[u][i] = graph[graph[u][i-1]][i-1];
				
		Q=Read(), K=Read(), S=Read();
		int last=0;
		while(Q--){
			int vi =Read(), pi = Read();
			vi=(vi + K * last - 1) % n + 1;
			pi=(pi + K * last) % (S + 1);
			for(int j=22; j>=0; j--)
				if(graph[vi][j] && val[graph[vi][j]] > pi) vi = graph[vi][j];
			printf("%lld\n",last = mn[vi]);
		}
	}
	return 0;
}