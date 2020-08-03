#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<set>
#define int long long
using namespace std;
const int MaxN = 4e5 + 10;
int n, m, q;
int top, stack[MaxN], DFN[MaxN], LOW[MaxN], value[MaxN], size[MaxN], step, cntSquare, ans, allSize, cntdfn, serial[MaxN / 2];
multiset<int> multiSet[MaxN];

struct Graph{
	int head[MaxN], to[MaxN], nextEdge[MaxN], cntEdge;
	inline void AddEdge(int u, int v){
		cntEdge++;
		to[cntEdge] = v;
		nextEdge[cntEdge] = head[u];
		head[u] = cntEdge;
		cntEdge++;
		to[cntEdge] = u;
		nextEdge[cntEdge] = head[v];
		head[v] = cntEdge;
	}
}graph, tree;

struct SegmentTree{
	int l, r, minValue;
}seg[MaxN * 2];

struct Vertex{
	int depth, heavySon, father, dfn, subtreeSize, value, chainTop;
	bool isSquare;
}vertex[MaxN / 2];

#define thisSon tree.to[i]
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

inline void TarjanBuildTree(int cur){
	LOW[cur] = DFN[cur] = ++step;
	stack[++top] = cur;
	for(int i = graph.head[cur], des; i; i = graph.nextEdge[i]){
		des = graph.to[i];
		if(!DFN[des]){
			TarjanBuildTree(des);
			LOW[cur] = min(LOW[cur], LOW[des]);
			if(LOW[des] >= DFN[cur]){
				int t = 0;
				cntSquare++;
				tree.AddEdge(cntSquare, cur);
				do{
					t = stack[top--];
					tree.AddEdge(t, cntSquare);
				}while(t != des);
			}
		}
		else LOW[cur] = min(LOW[cur], DFN[des]);
	}
}

inline void DFS1(int x, int fa){
	vertex[x].subtreeSize = 1;
	vertex[x].father = fa;
	vertex[x].depth = vertex[fa].depth + 1;
	if(x <= n && fa) multiSet[fa].insert(vertex[x].value);
	for(int i = tree.head[x]; i; i = tree.nextEdge[i]){
		if(thisSon == fa) continue;
		DFS1(thisSon, x);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
	if(x > n) vertex[x].value = *multiSet[x].begin();
}

inline void DFS2(int x, int chaintop){
	vertex[x].dfn = ++cntdfn;
	serial[vertex[x].dfn] = x;
	vertex[x].chainTop = chaintop;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, chaintop);
	for(int i = tree.head[x]; i; i = tree.nextEdge[i]){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
}

inline void Build(int x, int l, int r){
	seg[x].l = l; seg[x].r = r;
	if(l == r){
		seg[x].minValue = vertex[serial[l]].value;
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	seg[x].minValue = min(seg[x*2].minValue, seg[x*2+1].minValue);
}

inline void Change(int x, int pos, int w){
	if(seg[x].l == seg[x].r){
		seg[x].minValue = w;
		return;
	}
	int mid = (seg[x].l + seg[x].r) / 2;
	if(pos <= mid) Change(x*2, pos, w);
	else Change(x*2+1, pos, w);
	seg[x].minValue = min(seg[x*2].minValue, seg[x*2+1].minValue);
}

inline int Ask(int x, int ql, int qr){
	if(ql <= seg[x].l && seg[x].r <= qr) return seg[x].minValue;
	int mid = (seg[x].l + seg[x].r) / 2;
	int res = INT_MAX;
	if(ql <= mid) res = min(res, Ask(x*2, ql, qr));
	if(qr > mid) res = min(res, Ask(x*2+1, ql, qr));
	return res;
}

inline int WayAsk(int x, int y){
	int res = INT_MAX;
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		res = min(res, Ask(1, vertex[xTop].dfn, vertex[x].dfn));
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	res = min(res, Ask(1, vertex[x].dfn, vertex[y].dfn));
	if(x > n) res = min(res, vertex[vertex[x].father].value);
	return res;
}

signed main(){
	scanf("%lld%lld%lld", &n, &m, &q);
	for(int i=1;i<=n;i++)
		scanf("%lld", &vertex[i].value);
	cntSquare = n;
	//vertex[0].value = INT_MAX;
	for(int i=1;i<=m;i++){
		int u, v;
		scanf("%lld%lld", &u, &v);
		graph.AddEdge(u, v);
	}
	TarjanBuildTree(1);
	DFS1(1, 0);
	DFS2(1, 1);
	Build(1, 1, cntSquare);
//	for(int i=1;i<=cntSquare;i++)
//		printf("%lld %lld\n", vertex[i].subtreeSize, vertex[i].dfn);
	while(q--){
		char op[5];
		int a, b;
		scanf("%s%lld%lld", op, &a, &b);
		if(op[0] == 'C'){
			if(vertex[a].father > n){
				multiSet[vertex[a].father].erase(multiSet[vertex[a].father].find(vertex[a].value));
				multiSet[vertex[a].father].insert(b);
				vertex[vertex[a].father].value = *multiSet[vertex[a].father].begin();
				Change(1, vertex[vertex[a].father].dfn, vertex[vertex[a].father].value);
			}
			vertex[a].value = b;
			Change(1, vertex[a].dfn, b);
		}
		else printf("%lld\n",WayAsk(a, b));
	}
	//printf("%lld", vertex[10].value);
}