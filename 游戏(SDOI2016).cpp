#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, Inf = 123456789123456789;
int n, m, cntEdge, cntSeg, idx[MaxN], cntDFN;
struct Edge{
	int destination, nextEdge, length;
}edge[MaxN*2];
struct SegmentTree{
	int min, lowest;
}tree[MaxN*4];
struct Vertex{
	int head;
	int DFN, father, depth, chainTop, heavySon, subtreeSize, dist;
}vertex[MaxN];
struct Segment{
	int k, b;
}segment[MaxN*2];
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop
#define thisSon edge[i].destination
#define thisLow tree[x].lowest

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

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = vertex[u].head;
	edge[cntEdge].length = w;
	vertex[u].head = cntEdge;
	return;
}

inline int Gety(int serial, int x){
	return segment[serial].k * vertex[idx[x]].dist + segment[serial].b;
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i = vertex[x].head; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].father = x;
		vertex[thisSon].depth = vertex[x].depth + 1;
		vertex[thisSon].dist = vertex[x].dist + edge[i].length;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
	return;
}

inline void DFS2(int x, int top){
	vertex[x].DFN = ++cntDFN;
	idx[cntDFN] = x;
	vertex[x].chainTop = top;
	if(vertex[x].heavySon) DFS2(vertex[x].heavySon, top);
	for(int i = vertex[x].head; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
	return;
}

inline int LCA(int x, int y){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	return x;
}

inline void Change(int x, int l, int r, int ql, int qr, int serial){
	if(l == r){
		if(Gety(serial, l) < Gety(thisLow, l)){
			thisLow = serial;
			tree[x].min = Gety(serial, l);
			return;
		}
		return;
	}
	int mid = (l+r) >> 1;
	if(ql <= l && r <= qr){
		if(Gety(serial, l) >= Gety(thisLow, l) && Gety(serial, r) >= Gety(thisLow, r)) return;
		else if(Gety(serial, l) < Gety(thisLow, l) && Gety(serial, r) < Gety(thisLow, r)) thisLow = serial;
		else{
			if(segment[serial].k < segment[thisLow].k){
				if(Gety(serial, mid) <= Gety(thisLow, mid)){
					Change(x<<1, l, mid, ql, qr, thisLow);
					thisLow = serial;
				}
				else Change(x<<1|1, mid+1, r, ql, qr, serial);
			}
			else{
				if(Gety(serial, mid) <= Gety(thisLow, mid)){
					Change(x<<1|1, mid+1, r, ql, qr, thisLow);
					thisLow = serial;
				}
				else Change(x<<1, l, mid, ql, qr, serial);
			}
		}
		tree[x].min = min(tree[x].min, min(Gety(thisLow, l),Gety(thisLow, r)));
		tree[x].min = min(tree[x].min, min(tree[x<<1].min, tree[x<<1|1].min));
		return;
	}
	if(ql <= mid) Change(x<<1, l, mid, ql, qr, serial);
	if(qr > mid) Change(x<<1|1, mid+1, r, ql, qr, serial);
	tree[x].min = min(tree[x].min, min(tree[x<<1].min, tree[x<<1|1].min));
	return;
}

inline int Ask(int x, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr) return tree[x].min;
	int res = min(Gety(thisLow, max(l,ql)), Gety(thisLow, min(r,qr)));
	int mid = (l+r) >> 1;
	if(ql <= mid) res = min(res, Ask(x<<1, l, mid, ql, qr));
	if(qr > mid) res = min(res, Ask(x<<1, mid+1, r, ql, qr));
	return res;
}

inline void Modify(int x, int y, int serial){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		Change(1, 1, cntDFN, vertex[xTop].DFN, vertex[x].DFN, serial);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	Change(1, 1, cntDFN, vertex[x].DFN, vertex[y].DFN, serial);
	return;
}

inline int Query(int x, int y){
	int res = Inf;
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		res = min(res, Ask(1, 1, cntDFN, vertex[xTop].DFN, vertex[x].DFN));
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	res = min(res, Ask(1, 1, cntDFN, vertex[x].DFN, vertex[y].DFN));
	return res;
}

signed main(){
	n = Read(), m = Read();
	segment[0] = (Segment){0,Inf};
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w), AddEdge(v, u, w);
	}
	vertex[1].depth = 1;
	DFS1(1);
	DFS2(1, 1);
//	for(int i=1; i<=n; i++){
//		printf("%lld %lld %lld %lld\n", vertex[i].DFN, vertex[i].heavySon, vertex[i].depth, vertex[i].dist);
//	}
	for(int i=1; i<=cntDFN*4; i++)
		tree[i].min = Inf;
//	for(int i=1; i<=cntDFN; i++){
//		printf("%lld ", idx[i]);
//	}
	while(m--){
		int op = Read(), s = Read(), t = Read();
		if(op == 1){
			int a = Read(), b = Read(), lca = LCA(s,t);
//			printf("%lld\n", lca);
			cntSeg++;
			segment[cntSeg].k = -a;
			segment[cntSeg].b = a * vertex[s].dist + b;
			Modify(s, lca, cntSeg);
			cntSeg++;
			segment[cntSeg].k = a;
			segment[cntSeg].b = a * (vertex[s].dist - 2 * vertex[lca].dist) + b;
			Modify(lca, t, cntSeg);
		}
		else printf("%lld\n", Query(s,t));
	}
//	for(int i=1; i<=cntDFN*4; i++){
//		printf("%lld %lld\n", tree[i].min, tree[i].lowest);
//	}
//	for(int i=1; i<=cntSeg; i++){
//		printf("%lld %lld\n", segment[i].k, segment[i].b);
//	}
	return 0;
}