#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int MaxN = 100005;
typedef long long ll;
struct Edge{
    int destination, value, nextEdge;
}edge[MaxN*2];
struct SegmentTree{
    int x,y;
    ll length;
}seg[MaxN*4];
struct Vertex{
    int heavySon, chainTop, depth, father, subtreeSize, DFN;
    ll dis;
}vertex[MaxN];
int n, head[MaxN], cntEdge, cntDFN, pos[MaxN];

#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

inline void AddEdge(int u, int v, int w){
    cntEdge++;
	edge[cntEdge] = (Edge){v, w, head[u]};
    head[u] = cntEdge;
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i=head[x]; i; i=edge[i].nextEdge){
        if(thisSon == vertex[x].father) continue;
        vertex[thisSon].depth = vertex[x].depth + 1;
		vertex[thisSon].dis = vertex[x].dis + edge[i].value;
        vertex[thisSon].father = x;
		DFS1(thisSon);
        vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
    }
}

inline void DFS2(int x, int top){
    cntDFN++;
	vertex[x].DFN = cntDFN;
    pos[cntDFN] = x;
    vertex[x].chainTop = top;
    if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i=head[x]; i; i=edge[i].nextEdge){
        if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
        DFS2(thisSon, thisSon);
    }
}

inline ll GetLength(int x, int y){
	if(!x || !y) return 0;
	ll ans = vertex[x].dis + vertex[y].dis;
	while(xTop != yTop){
        if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
        x = vertex[xTop].father;
    }
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
    ans -= vertex[x].dis*2;
    return ans;
}

inline SegmentTree MakeSeg(int x, int y){
    return (SegmentTree){x, y, GetLength(x,y)};
}

inline SegmentTree Longer(SegmentTree x, SegmentTree y){
    return x.length < y.length ? y:x;
}

inline SegmentTree Merge(SegmentTree a,SegmentTree b){
	return Longer(Longer(a,b), Longer(Longer(MakeSeg(a.x,b.x), MakeSeg(a.x,b.y)), Longer(MakeSeg(a.y,b.x), MakeSeg(a.y,b.y))));
}

inline void Build(int l,int r,int x){
	if(l==r){
        seg[x] = (SegmentTree){pos[l],pos[l],0};
        return;
    }
	int mid=(l+r)/2;
	Build(l, mid, x*2);
	Build(mid+1,r,x*2+1);
	seg[x] = Merge(seg[x*2], seg[x*2+1]);
}

inline SegmentTree Ask(int x,int l,int r,int L,int R){
	if(L>R) return (SegmentTree){0,0,0};
	if(L<=l && r<=R) return seg[x];
	int mid=(l+r)/2;
    SegmentTree ans = (SegmentTree){0,0,-1};
	if(L <= mid) ans = Ask(x*2, l, mid, L, R);
	if(mid < R) ans = Merge(ans, Ask(x*2+1, mid+1, r, L, R));
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int x, y, w;
        scanf("%d%d%d",&x,&y,&w);
		AddEdge(x,y,w), AddEdge(y,x,w);
	}
	//vertex[1].depth = 1;
	DFS1(1);
    DFS2(1,1);
    Build(1,n,1);
	ll ans = 0;
	for(int i=2;i<=n;i++){
		SegmentTree a,b,c;
		a=Ask(1, 1, n, vertex[i].DFN, vertex[i].DFN+vertex[i].subtreeSize-1);
		b=Ask(1, 1, n, 1, vertex[i].DFN-1);
		c=Ask(1, 1, n, vertex[i].DFN+vertex[i].subtreeSize, n);
		ans = max(ans, a.length + Merge(b,c).length);
	}
	printf("%lld\n",ans);
}