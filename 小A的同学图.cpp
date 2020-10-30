#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
#define fake false
using namespace std;
const int MaxN = 500005;
int n, m, q, s, opt;
int minw[MaxN], c[MaxN], f[MaxN]; // 女の子

class Tree{
	public:
	int head[MaxN], cntEdge;
	struct Edge{
		int destination, nextEdge, value;
		bool operator < (const Edge &y) const{
			return value < y.value;
		}
	}edge[MaxN*2];
	
	inline void AddEdge(int u, int v, int w){
		cntEdge++;
		edge[cntEdge].destination = v;
		edge[cntEdge].nextEdge = head[u];
		edge[cntEdge].value = w;
		head[u] = cntEdge;
		return;
	}
}tree;

class Graph{
	public:
	int father[MaxN], cntEdge;
	struct Edge{
		int from, to, value;
		bool operator < (const Edge &y) const{
			return value < y.value;
		}
	}edge[MaxN*2];
	
	inline void AddEdge(int u, int v, int w){
		cntEdge++;
		edge[cntEdge] = (Edge){u,v,w};
		return;
	}
	
	inline int Find(int x){
		return father[x] == x? x : father[x] = Find(father[x]);
	}
	
	inline void Kruskal(){
		for(int i=1; i<=n; i++)
			father[i] = i;
		for(int i=1; i<=m; i++){
			int u = Find(edge[i].from), v = Find(edge[i].to);
			if(u != v){
				tree.AddEdge(edge[i].from, edge[i].to, edge[i].value);
				tree.AddEdge(edge[i].to, edge[i].from, edge[i].value);
				father[u] = v;
			}
		}
	}
}graph;

inline void DFS(int x, int fa, int mn){
	minw[c[x]] = min(minw[c[x]], mn);
	for(int i = tree.head[x]; i; i = tree.edge[i].nextEdge){
		int y = tree.edge[i].destination, z = tree.edge[i].value;
		if(y == fa) continue;
		DFS(y, x, max(mn,z));
	}
	return;
}

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

signed main(){
//	freopen("sample.in", "r", stdin);
//	freopen("my.out", "w", stdout);
	n = Read(), m = Read(), q = Read(), s = Read(), opt = Read();
	int mod, types=0;
	if(opt == 1) mod = Read();
	for(int i=1; i<=n; i++){
		c[i] = Read();
		types = max(types, c[i]);
	}
	for(int i=1; i<=types; i++)
		minw[i] = INT_MAX;
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		graph.AddEdge(u, v, w);
	}
	sort(graph.edge+1, graph.edge+1+graph.cntEdge);
	graph.Kruskal();
	DFS(s, 0, 0);
	for(int i=1; i<=types; i++)
		f[i] = minw[i];
	sort(f+1, f+1+types);
	f[++types] = INT_MAX;
	int las = 0;
	while(q--){
		int l = Read(), r = Read();
		if(opt == 1){
			l = (l ^ las) % mod + 1;
			r = (r ^ las) % mod + 1;
		}
		if(l > r) swap(l,r);
		int ans = 0, pos = l;
		for(int i=1; i<=types; i++){
			if(f[i] > r){
				ans += (r-pos+1) * (i-1);
				break;
			}
			if(f[i] <= pos) continue;
			ans += (f[i]-pos) * (i-1);
			pos = f[i];
		}
		if(opt == 1) las = ans;
		printf("%lld\n", ans);
	}
	return 0;
}