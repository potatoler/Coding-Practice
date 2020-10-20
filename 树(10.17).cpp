#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
#define int long long
#define thisSon edge[i].destiVertex
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop
using namespace std;
const int MaxN = 1000005, Mod = 1000000007;
int n, m, root, finalVal[MaxN];
struct Vertex{
	int val, father, depth, subtreeSize, heavySon, chainTop, DFN;
}vertex[MaxN];
struct Edge{
	int destiVertex, nextEdge;
}edge[MaxN * 2];
struct SegmentTree{
	int data, addTag, l, r;
}seg[MaxN * 4];
int tot, head[MaxN], cntDFN;

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

inline void AddEdge(int u,int v){
	tot++;
	edge[tot].destiVertex = v;
	edge[tot].nextEdge = head[u];
	head[u] = tot;
	return;
}

inline void PassTag(int x){
	seg[x*2].data = (seg[x*2].data + seg[x].addTag * (seg[x*2].r - seg[x*2].l + 1) % Mod) % Mod;
	seg[x*2+1].data = (seg[x*2+1].data + seg[x].addTag * (seg[x*2+1].r - seg[x*2+1].l + 1) % Mod) % Mod;
	seg[x*2].addTag = (seg[x*2].addTag + seg[x].addTag) % Mod;
	seg[x*2+1].addTag = (seg[x*2+1].addTag + seg[x].addTag) % Mod;
	seg[x].addTag = 0;
}

inline void Build(int x,int l,int r){
	seg[x].l = l, seg[x].r = r;
	if(seg[x].l == seg[x].r){
		seg[x].data = finalVal[l];
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
	seg[x].data = (seg[x*2].data + seg[x*2+1].data) % Mod;
}

inline int Ask(int x,int l,int r){
	int ans = 0;
	if(seg[x].l >= l && seg[x].r <= r) return seg[x].data;
	if(seg[x].addTag) PassTag(x);
	int mid = (seg[x].l + seg[x].r) / 2;
	if(l <= mid) ans = (ans + Ask(x*2, l, r)) % Mod;
	if(r > mid) ans = (ans + Ask(x*2+1, l, r)) % Mod;
	return ans % Mod;
}

inline void Addition(int x, int l, int r, int z){
	if(l <= seg[x].l && r >= seg[x].r){
		seg[x].data = (seg[x].data + z * (seg[x].r - seg[x].l + 1)) % Mod;
		seg[x].addTag = (seg[x].addTag + z) % Mod;
		return;
	}
	if(seg[x].addTag) PassTag(x);
	int mid = (seg[x].l + seg[x].r) / 2;
	if(l <= mid) Addition(x*2, l, r, z);
	if(r > mid) Addition(x*2+1, l, r, z);
	seg[x].data = (seg[x*2].data + seg[x*2+1].data) % Mod;
}

inline int LCA(int x, int y){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	return x;
}

inline int WayAsk(int x,int y){
	int ans=0;
	while(xTop != yTop){
			if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
			ans = (ans + Ask(1, vertex[xTop].DFN, vertex[x].DFN)) % Mod;
			x = vertex[xTop].father;
		}
	if(vertex[x].depth > vertex[y].depth) swap(x, y);
	ans = (ans + Ask(1, vertex[x].DFN, vertex[y].DFN)) % Mod;
	return ans % Mod;
}

inline void WayAdd(int x,int y,int k){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		Addition(1, vertex[xTop].DFN, vertex[x].DFN,k);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x, y);
	Addition(1, vertex[x].DFN, vertex[y].DFN, k);
}

inline void SubtreeAdd(int x, int z){
	Addition(1, vertex[x].DFN ,vertex[x].DFN + vertex[x].subtreeSize - 1, z % Mod);
}

inline int SubtreeAsk(int x){
	return Ask(1, vertex[x].DFN ,vertex[x].DFN + vertex[x].subtreeSize - 1);
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].father = x;
		vertex[thisSon].depth = vertex[x].depth + 1;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
	return;
}

inline void DFS2(int x, int top){
	vertex[x].DFN = ++cntDFN;
	finalVal[vertex[x].DFN] = vertex[x].val;
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=2; i<=n; i++){
		int fa = Read();
		AddEdge(fa, i), AddEdge(i, fa);
	}
	for(int i=1; i<=n; i++)
		vertex[i].val = Read();
	DFS1(1);
	DFS2(1,1);
	Build(1,1,n);
	while(m--){
		int op = Read();
		if(op == 1){
			int u = Read(), v = Read();
			WayAdd(u, u, v);
		}
		if(op == 2){
			int a = Read(), b = Read(), v = Read();
			SubtreeAdd(LCA(a,b), v);
		}
		if(op == 3){
			int a = Read(), b = Read();
			int lca = LCA(a,b);
			printf("%lld %lld\n", lca, WayAsk(lca, lca));
		}
		if(op == 4){
			int u = Read();
			printf("%lld\n",SubtreeAsk(u));
		}
	}
}