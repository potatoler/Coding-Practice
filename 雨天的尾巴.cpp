#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
const int MaxN = 100005;
int n, m, cntEdge, cntDFN, head[MaxN], ser[MaxN], ans[MaxN];
struct Edge{
    int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
    int father, depth, DFN, subtreeSize, chainTop, heavySon;
    vector< pair<int,int> > item;
}vertex[MaxN];
struct SegmentTree{
    int l, r, data, ans;
}seg[MaxN*4];
//vector<pair<int,int> >t[MaxN];
#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

inline void AddEdge(int u, int v){
    cntEdge++;
    edge[cntEdge].destination = v;
    edge[cntEdge].nextEdge = head[u];
    head[u] = cntEdge;
}

inline void DFS1(int x){
    vertex[x].subtreeSize = 1;
    for(int i=head[x];i;i=edge[i].nextEdge){
        if(thisSon == vertex[x].father) continue;
        vertex[thisSon].depth = vertex[x].depth + 1;
        vertex[thisSon].father = x;
        DFS1(thisSon);
        vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
        if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
    }
}

inline void DFS2(int x, int top){
    vertex[x].DFN = ++cntDFN;
    ser[vertex[x].DFN] = x;
    vertex[x].chainTop = top;
    if(!vertex[x].heavySon) return;
    DFS2(vertex[x].heavySon, top);
    for(int i=head[x];i;i=edge[i].nextEdge){
        if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
        DFS2(thisSon, thisSon);
    }
}

inline void Build(int x,int l,int r){
	seg[x].l = l; seg[x].r = r;
	if(l == r) return;
	int mid = (l+r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
}

inline void Statistic(int x, int kind, int num){
	if(seg[x].l == seg[x].r){
		seg[x].data += num;
		seg[x].data? seg[x].ans = kind : seg[x].ans=0;
		return;
	}
	int mid = (seg[x].l + seg[x].r) / 2;
	if(mid >= kind) Statistic(x*2, kind, num);
	else Statistic(x*2+1, kind, num);
	seg[x].data = max(seg[x*2].data, seg[x*2+1].data);
	if(seg[x].data == seg[x*2].data) seg[x].ans = seg[x*2].ans;
	else seg[x].ans = seg[x*2+1].ans;
}

inline void TreeAdd(int x,int y,int z){
	while(xTop!=yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		vertex[vertex[xTop].DFN].item.push_back(make_pair(z,1));
		vertex[vertex[x].DFN+1].item.push_back(make_pair(z,-1));
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	vertex[vertex[x].DFN].item.push_back(make_pair(z,1));
	vertex[vertex[y].DFN+1].item.push_back(make_pair(z,-1));
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u, v;
        scanf("%d%d",&u,&v);
		AddEdge(u,v);
        AddEdge(v,u);
	}
	DFS1(1);
    DFS2(1,1);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		TreeAdd(x,y,z);
	}
	Build(1,1,100005);
	for(int i=1;i<=n;i++){
		int kind = vertex[i].item.size();
		for(int j=0;j<kind;j++)
		    Statistic(1,vertex[i].item[j].first,vertex[i].item[j].second);
		ans[ser[i]] = seg[1].ans;
	}
	for(int i=1;i<=n;i++)
	    printf("%d\n",ans[i]);
	return 0;
}