#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MaxN = 100010;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];
struct Vertex{
	int father, depth, subtreeSize, chainTop, DFN, heavySon, colour;
}vertex[MaxN];
struct SegmentTree{
	int l, r, sum, colour, tag;
	int lc, rc;
}seg[MaxN*4];
int n, m, cntEdge, cntDFN, head[MaxN], serial[MaxN];

#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop
#define lSon x*2
#define rSon x*2+1

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i=head[x]; i; i=edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].father = x;
		vertex[thisSon].depth = vertex[x].depth + 1;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
}

inline void DFS2(int x, int top){
	cntDFN++;
	vertex[x].DFN = cntDFN;
	serial[vertex[x].DFN] = x;
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i=head[x]; i; i=edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
}

inline void PassTag(int x){
	if(seg[x].tag != 0 && seg[x].l != seg[x].r){
		seg[lSon].tag = seg[rSon].tag = seg[x].tag;
		seg[lSon].colour = seg[rSon].colour = seg[x].tag;
		seg[lSon].lc = seg[rSon].lc = seg[lSon].rc = seg[rSon].rc = seg[x].tag;
		seg[lSon].sum = seg[rSon].sum = 1;
		seg[x].tag = 0;
	}
}
inline void Update(int x){
	seg[x].sum = seg[lSon].sum + seg[rSon].sum;
	if(seg[lSon].rc == seg[rSon].lc) seg[x].sum--;
	seg[x].lc = seg[lSon].lc; seg[x].rc = seg[rSon].rc;
}

inline void Build(int x, int l, int r){
	seg[x].l = l; seg[x].r = r;
	if(l == r){
		seg[x].lc = seg[x].rc = seg[x].colour = vertex[serial[l]].colour;
		seg[x].sum = 1;
		return;
	}
	int mid = (l + r) / 2;
	Build(lSon, l, mid); Build(rSon, mid+1, r);
	Update(x);
}

inline void Colour(int x, int l, int r, int c){
	PassTag(x);
	if(seg[x].l == l && seg[x].r == r){
		seg[x].colour = c;
		seg[x].tag = c;
		seg[x].sum = 1;
		seg[x].lc = seg[x].rc = c;
		return;
	}
	int mid = (seg[x].l + seg[x].r) / 2;
	if(r <= mid) Colour(lSon, l, r, c);
	else if(l > mid) Colour(rSon, l, r, c);
	else{
		Colour(lSon, l, mid, c);
		Colour(rSon, mid+1, r, c);
	}
	Update(x);
}

inline int AskSum(int x, int l, int r){
	PassTag(x);
	if(seg[x].l == l && seg[x].r == r) return seg[x].sum;
	int mid = (seg[x].l + seg[x].r) / 2;
	if(r <= mid) return AskSum(lSon, l, r);
	else if(l > mid) return AskSum(rSon, l, r);
	else{
		if(seg[lSon].rc == seg[rSon].lc) return (AskSum(lSon, l, mid) + AskSum(rSon, mid+1, r) - 1);
		else return (AskSum(lSon, l, mid) + AskSum(rSon, mid+1, r));
	}
}

inline int AskColour(int x, int l, int r){
	PassTag(x);
	if(seg[x].l == l && seg[x].r == r) return seg[x].colour;
	int mid = (seg[x].l + seg[x].r) / 2;
	if(l <= mid) return AskColour(lSon, l, r);
	else return AskColour(rSon, l, r);
}


inline void WayColour(int x, int y, int c){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x, y);
		Colour(1, vertex[xTop].DFN, vertex[x].DFN, c);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x, y);
	Colour(1, vertex[x].DFN, vertex[y].DFN, c);
}

inline int WayAsk(int x, int y){
	int ans = 0, sonColour, fatherColour;
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x, y);
		ans += AskSum(1, vertex[xTop].DFN, vertex[x].DFN);
		sonColour = AskColour(1, vertex[xTop].DFN, vertex[xTop].DFN);
		fatherColour = AskColour(1, vertex[vertex[xTop].father].DFN, vertex[vertex[xTop].father].DFN);
		if(sonColour == fatherColour) ans--;
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x, y);
	ans += AskSum(1, vertex[x].DFN, vertex[y].DFN);
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&vertex[i].colour);
	for(int i=1;i<n;i++){
		int u, v;
		scanf("%d%d",&u,&v);
		AddEdge(u, v); AddEdge(v, u);
	}
	DFS1(1);
	DFS2(1,1);
	Build(1, 1, n);
	char op; int a, b, c;
	for(int i=1;i<=m;i++){
		cin>>op;
		if(op == 'Q'){
			scanf("%d%d",&a,&b);
			printf("%d\n",WayAsk(a, b));
		}
		else{
			scanf("%d%d%d",&a,&b,&c);
			WayColour(a, b, c);
		}
	}
	return 0;
}