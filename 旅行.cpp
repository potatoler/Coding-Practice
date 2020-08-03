#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int MaxN = 100005;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int depth, father, subtreeSize, DFN, heavySon, chainTop, point, religion;
}vertex[MaxN];
struct SegmentTree{
	int lSon, rSon, maxPoint, totPoint;
}seg[MaxN*20];
int n, q, cntEdge, cntSeg, cntDFN, head[MaxN], serial[MaxN], root[MaxN];
char op[5];

#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

inline void AddEdge(int u, int v){
	edge[++cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i=head[x]; i; i=edge[i].nextEdge){
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
	serial[vertex[x].DFN] = x;
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i=head[x]; i; i=edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
}

inline void Update(int &x, int l, int r, int w, int pos){
	if(!x) x = ++cntSeg;
	seg[x].maxPoint = max(seg[x].maxPoint, w);
	seg[x].totPoint += w;
	if(l == r) return;
	int mid = (l + r) / 2;
	if(mid >= pos) Update(seg[x].lSon, l, mid, w, pos);
	else Update(seg[x].rSon, mid+1, r, w, pos);
}

inline void Delete(int x, int l, int r, int pos){
	if(l == r){
		seg[x].totPoint = 0;
		seg[x].maxPoint = 0;
		return;
	}
	int mid = (l + r) / 2;
	if(mid >= pos) Delete(seg[x].lSon, l, mid, pos);
	else Delete(seg[x].rSon, mid+1, r, pos);
	seg[x].totPoint = seg[seg[x].lSon].totPoint + seg[seg[x].rSon].totPoint;
	seg[x].maxPoint = max(seg[seg[x].lSon].maxPoint, seg[seg[x].rSon].maxPoint);
}

inline int SegTotal(int x, int segl, int segr, int l, int r){
	if(r < segl || l > segr) return 0;
	if(r >= segr && l <= segl) return seg[x].totPoint;
	int mid = (segl + segr) / 2;
	return SegTotal(seg[x].lSon, segl, mid, l, r) + SegTotal(seg[x].rSon, mid+1, segr, l, r);
}

inline int SegMax(int x, int segl, int segr, int l, int r){
	if(r < segl || l > segr) return 0;
	if(r >= segr && l <= segl) return seg[x].maxPoint;
	int mid = (segl + segr) / 2;
	return max(SegMax(seg[x].lSon, segl, mid, l, r), SegMax(seg[x].rSon, mid+1, segr, l, r));
}

inline int WayTot(int x, int y, int rel){
	int ans = 0;
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x, y);
		ans += SegTotal(root[rel], 1, n, vertex[xTop].DFN, vertex[x].DFN);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x, y);
	ans += SegTotal(root[rel], 1, n, vertex[x].DFN, vertex[y].DFN);
	return ans;
}

inline int WayMax(int x, int y, int rel){
	int ans = 0;
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x, y);
		ans = max(ans, SegMax(root[rel], 1, n, vertex[xTop].DFN, vertex[x].DFN));
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x, y);
	ans = max(ans, SegMax(root[rel], 1, n, vertex[x].DFN, vertex[y].DFN));
	return ans;
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&vertex[i].point, &vertex[i].religion);
	for(int i=1;i<n;i++){
		int u, v;
		scanf("%d%d",&u,&v);
		AddEdge(u, v);
		AddEdge(v, u);
	}
	DFS1(1);
	DFS2(1,1);
	for(int i=1;i<=n;i++)
		Update(root[vertex[i].religion], 1, n, vertex[i].point, vertex[i].DFN);
	for(int i=1;i<=q;i++){
		int x, y;
		scanf("%s%d%d",op, &x, &y);
		switch(op[1]){
			case 'C':{
				Delete(root[vertex[x].religion], 1, n, vertex[x].DFN);
				Update(root[y], 1, n, vertex[x].point, vertex[x].DFN);
				vertex[x].religion = y;
				break;
			}
			case 'W':{
				Delete(root[vertex[x].religion], 1, n, vertex[x].DFN);
				Update(root[vertex[x].religion], 1, n, y, vertex[x].DFN);
				vertex[x].point = y;
				break;
			}
			case 'S':{
				printf("%d\n",WayTot(x, y, vertex[x].religion));
				break;
			}
			case 'M':{
				printf("%d\n",WayMax(x, y, vertex[x].religion));
				break;
			}
		}
	}
//	for(int i=1;i<=n;i++)
//		printf("%d %d %d %d %d %d\n", i, vertex[i].father, vertex[i].heavySon, vertex[i].subtreeSize, vertex[i].chainTop, vertex[i].DFN);
	return 0;
}