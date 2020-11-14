#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 300005, MaxM = 1000006;
int n, m, q;

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

class MinimumSpanningTree{
	private:
	int head[MaxN], cntEdge, idx[MaxN], cntDFN;
	struct Edge{
		int destination, nextEdge, value; 
	}edge[MaxN*2];
	struct SegmentTree{
		int l, r, max, min;
	}tree[MaxN*4];
	
	public:
	struct Vertex{
		int DFN, father, heavySon, subtreeSize, chainTop, depth, value, min_1st, min_2nd;
	}vertex[MaxN];
	#define thisSon edge[i].destination
	#define xTop vertex[x].chainTop
	#define yTop vertex[y].chainTop
			
	inline void AddEdge(int u, int v, int w){
		cntEdge++;
		edge[cntEdge].destination = v;
		edge[cntEdge].nextEdge = head[u];
		edge[cntEdge].value = w;
		head[u] = cntEdge;
	}
	
	inline void DFS1(int x){
		vertex[x].subtreeSize = 1;
		if(head[x]) vertex[x].min_1st = vertex[x].min_2nd = INT_MAX;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			if(thisSon == vertex[x].father) continue;
			if(edge[i].value < vertex[x].min_1st){
				vertex[x].min_2nd = vertex[x].min_1st;
				vertex[x].min_1st = edge[i].value;
			}
			else if(edge[i] < min_2nd){
				vertex[x]
			}
			vertex[thisSon].father = x;
			vertex[thisSon].value = edge[i].value;
			vertex[thisSon].depth = vertex[x].depth + 1;
			DFS1(thisSon);
			if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
			vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		}
		return;
	}
	
	inline void DFS2(int x, int top){
		vertex[x].DFN = ++cntDFN;
		idx[cntDFN] = x;
		vertex[x].chainTop = top;
		if(!vertex[x].heavySon) return;
		DFS2(vertex[x].heavySon, top);
		for(int i = head[x]; i; i = edge[i].nextEdge){
			if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
			DFS2(thisSon, thisSon);
		}
		return;
	}
	
	inline void Update(int x){
		tree[x].max = max(tree[x<<1].max, tree[x<<1|1].max);
		tree[x].min = min(tree[x<<1].min, tree[x<<1|1].min);
		return;
	}
	
	inline void Build(int x, int l, int r){
		tree[x].l = l, tree[x].r = r;
		if(l == r){
			tree[x].max = vertex[idx[l]].value;
			tree[x].min = vertex[idx[l]].min;
			return;
		}
		int mid = (l+r) >> 1;
		Build(x<<1, l, mid);
		Build(x<<1|1, mid+1, r);
		Update(x);
		return;
	}
	
	inline pair<int,int> Query(int x, int ql, int qr){
		if(ql <= tree[x].l && tree[x].r <= qr) return make_pair(tree[x].max, tree[x].min);
		int mid = (tree[x].l + tree[x].r) >> 1;
		pair<int,int> res = make_pair(0, INT_MAX);
		if(ql <= mid){
			pair<int,int> tmp = Query(x<<1, ql, qr);
			res.first = max(res.first, tmp.first);
			res.second = min(res.second, tmp.second);
		}
		if(qr > mid){
			pair<int,int> tmp = Query(x<<1|1, ql, qr);
			res.first = max(res.first, tmp.first);
			res.second = min(res.second, tmp.second);
		}
		return res;
	}
	
	inline int WayAsk(int x, int y){
		pair<int,int> res = make_pair(0, INT_MAX);
		while(xTop != yTop){
			if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
			pair<int,int> tmp = Query(1, vertex[xTop].DFN, vertex[x].DFN);
			res.first = max(res.first, tmp.first);
			res.second = min(res.second, tmp.second);
			x = vertex[xTop].father;
		}
		if(vertex[x].depth > vertex[y].depth) swap(x,y);
		pair<int,int> tmp = Query(1, vertex[x].DFN+1, vertex[y].DFN);
		res.first = max(res.first, tmp.first);
		res.second = min(res.second, tmp.second);
		if(vertex[x].DFN != 1) res.second = min(res.second, Query(1, vertex[x].DFN, vertex[x].DFN).first);
		return max(res.first, res.second);
	}
}MST;

class Graph{
	private:
		
	int father[MaxN], tot;
	struct Edge{
		int from, to, val;
		bool operator < (const Edge &y) const{
			return val < y.val;
		}
	}edge[MaxM];
	
	public:
	inline void Build(int x){
		for(int i=1; i<=x; i++){
			int u = Read(), v = Read(), w = Read();
			edge[i] = (Edge){u,v,w};
		}
		return;
	}
	
	inline int Find(int x){
		return father[x] == x ? x : father[x] = Find(father[x]);
	}

	inline bool Merge(int x, int y){
		int fx = Find(x), fy = Find(y);
		if(fx != fy){
			father[fy] = fx;
			return true;
		}
		return false;
	}

	inline void Kruskal(){
		sort(edge+1, edge+1+m);
		for(int i=1; i<=n; i++)
			father[i] = i;
		for(int i=1; i<=m; i++){
			if(Merge(edge[i].from, edge[i].to)){
				tot++;
				MST.AddEdge(edge[i].from, edge[i].to, edge[i].val);
				MST.AddEdge(edge[i].to, edge[i].from, edge[i].val);
				if(tot == n) break;
			}
		}
	}
}graph;

signed main(){
	n = Read(), m = Read(), q = Read();
	graph.Build(m);
	graph.Kruskal();
	MST.DFS1(1);
	MST.DFS2(1,1);
	MST.Build(1, 1, n);
//	for(int i=1; i<=n; i++)
//		printf("%lld %lld\n", MST.vertex[i].value, MST.vertex[i].min);
	while(q--){
		int x = Read(), y = Read();
		printf("%lld\n", MST.WayAsk(x,y));
	}
	return 0;
}