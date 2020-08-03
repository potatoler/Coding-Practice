#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100005;
struct SegmentTree{
	int l, r;
	int lSon, rSon;
	int lc, rc, col;
	int cnt, tag;
}seg[MaxN*4];
struct Vertex{
	int father, depth, subtreeSize, chainTop, DFN, heavySon, colour;
}vertex[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
int n, m, cntEdge, cntDFN, serial[MaxN], head[MaxN];
int colourL, colourR, thisChainColour, anotherChainColour;

#define thisSon edge[i].destination
#define aTop vertex[a].chainTop
#define bTop vertex[b].chainTop

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
	seg[seg[x].lSon].tag = seg[seg[x].rSon].tag = seg[x].tag;
	seg[seg[x].lSon].cnt = seg[seg[x].rSon].cnt = 1;
	seg[seg[x].lSon].lc = seg[seg[x].lSon].rc = seg[x].lc;
	seg[seg[x].rSon].lc = seg[seg[x].rSon].rc = seg[x].rc;
	seg[x].tag = 0;
}

inline void Upload(int x){
	seg[x].lc = seg[seg[x].lSon].lc;
	seg[x].rc = seg[seg[x].rSon].rc;
	seg[x].cnt = seg[seg[x].lSon].cnt + seg[seg[x].rSon].cnt;
	if(seg[seg[x].lSon].rc == seg[seg[x].rSon].lc) seg[x].cnt--;
}

inline void Build(int x, int l, int r){
	seg[x].l = l; seg[x].r = r;
	seg[x].lSon = x*2; seg[x].rSon = x*2+1;
	if(l == r){
		seg[x].col = seg[x].lc = seg[x].rc = vertex[serial[l]].colour;
		seg[x].cnt = 1;
		return;
	}
	int mid = (l + r) / 2;
	Build(seg[x].lSon, l, mid);
	Build(seg[x].rSon, mid+1, r);
	Upload(x);
}

inline void Colour(int x, int l, int r, int w){
	if(seg[x].l >= l && seg[x].r <= r){
		seg[x].cnt = 1;
		seg[x].tag = w;
		seg[x].lc = seg[x].rc = w;
		return;
	}
	PassTag(x);
	int mid = (seg[x].l + seg[x].r) / 2;
	if(l <= mid) Colour(seg[x].lSon, l, r, w);
	if(r > mid) Colour(seg[x].rSon, l, r, w);
	Upload(x);
}

inline int Ask(int x, int l, int r){
	int L = seg[x].l, R = seg[x].r;
	if(l <= seg[x].l && seg[x].r <= r){
		if(l == seg[x].l) colourL = seg[x].lc;
		if(r == seg[x].r) colourR = seg[x].rc;
		return seg[x].cnt;
	}
	PassTag(x);
	int mid = (seg[x].l + seg[x].r) / 2;
	if(r <= mid) return Ask(seg[x].lSon, l, r);
	else if(l > mid) return Ask(seg[x].rSon, l, r);
	else if(seg[seg[x].lSon].rc == seg[seg[x].rSon].lc) return Ask(seg[x].lSon, l, r) + Ask(seg[x].rSon, l, r) - 1;
	else return Ask(seg[x].lSon, l, r) + Ask(seg[x].rSon, l, r);
}

inline void WayColour(int a, int b, int c){
	while(aTop != bTop){
		if(vertex[aTop].depth < vertex[bTop].depth) swap(a,b);
		Colour(1, vertex[aTop].DFN, vertex[a].DFN, c);
		a = vertex[aTop].father;
	}
	if(vertex[a].depth > vertex[b].depth) swap(a,b);
	Colour(1, vertex[a].DFN, vertex[b].DFN, c);
}

inline int WayAsk(int a, int b){
	int ans = 0;
	thisChainColour = anotherChainColour = 0;
	while(aTop != bTop){
		if(vertex[aTop].depth < vertex[bTop].depth) swap(a,b), swap(thisChainColour,anotherChainColour);
		ans += Ask(1, vertex[aTop].DFN, vertex[a].DFN);
		if(colourR == thisChainColour) ans--;
		thisChainColour = colourL;
		a = vertex[aTop].father;
	}
	if(vertex[a].depth > vertex[b].depth) swap(a,b), swap(thisChainColour,anotherChainColour);
	ans += Ask(1, vertex[a].DFN, vertex[b].DFN);
	if(colourL == thisChainColour) ans--;
	if(colourR == anotherChainColour) ans--; 
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&vertex[i].colour);
	for(int i=1;i<n;i++){
		int u, v;
		scanf("%d%d",&u,&v);
		AddEdge(u, v), AddEdge(v, u);
	}
//	for(int i=1;i<=cntEdge;i+=2)
//		printf("%d %d\n",edge[i].destination, edge[i].nextEdge);
	DFS1(1);
	DFS2(1,1);
//	for(int i=1;i<=n;i++)
//		printf("%d %d %d %d %d\n",vertex[i].father, vertex[i].subtreeSize, vertex[i].depth, vertex[i].chainTop, vertex[i].heavySon);
	Build(1, 1, n);
	for(int i=1;i<=m;i++){
		char op; int a, b, c;
		scanf("%c",&op);
		if(op == 'C'){
			scanf("%d%d%d",&a,&b,&c);
			WayColour(a, b, c);
		}
		if(op == 'Q'){
			scanf("%d%d",&a,&b);
			printf("%d\n",WayAsk(a, b));
		}
	}
	return 0;
}