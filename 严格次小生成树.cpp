#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MaxN = 100005, MaxM = 300005;
struct Edge{
	int from, to, value, used, nextEdge;
	bool operator < (const Edge &E) const{return value < E.value;}
}edge[MaxM * 2];
struct Vertex{
	int depth, father, heavySon, DFN, chainTop, subtreeSize, val;
}vertex[MaxN];
struct SegmentTree{
	int veryMax, secondMax;
}seg[MaxN * 4];
int n, m, head[MaxN], cntEdge, cntDFN, serial[MaxN], fa[MaxN];
ll MST, secondMST = 1e15;

#define thisSon edge[i].to
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

inline int secmax(int a, int b, int c, int d){
	int tmp[4] = {a, b, c, d};
	sort(tmp, tmp+4);
	for(int i=2; i>=0; i--)
		if(tmp[i] != tmp[i+1]) return tmp[i];
}

inline void AddEdge(int from, int to, int value, int used){
	cntEdge++;
	edge[cntEdge] = (Edge){from, to, value, used, head[from]};
	head[from] = cntEdge;
}

inline int Find(int x){
	return fa[x] == x? x : fa[x] = Find(fa[x]);
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i=head[x]; i; i=edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].depth = vertex[x].depth + 1;
		vertex[thisSon].father = x;
		vertex[thisSon].val = edge[i].value;
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

//inline void Build(int x, int l, int r){
//	seg[x].l = l;
//	seg[x].r = r;
//	if(l == r) return;
//	int mid = (l + r) / 2;
//	Build(x*2, l, mid);
//	Build(x*2+1, mid+1, r);
//}

inline void Change(int l, int r, int x, int w, int p){
	if(l == r){
		seg[x].veryMax = w;
		seg[x].secondMax = 0;
		return;
	}
	int mid = (l + r) / 2;
	if(p <= mid) Change(l, mid, x*2, w, p);
	else Change(mid+1, r, x*2+1, w, p);
	seg[x].secondMax = secmax(seg[x*2].veryMax, seg[x*2].secondMax, seg[x*2+1].veryMax, seg[x*2+1].secondMax);
	seg[x].veryMax = max(seg[x*2].veryMax, seg[x*2+1].veryMax);
}

inline SegmentTree Ask(int l, int r, int x, int ql, int qr){
	if(ql <= l && r <= qr) return seg[x];
	int mid = (l + r) / 2;
	if(ql <= mid && qr > mid){
		SegmentTree lans = Ask(l, mid, x*2, ql, qr), rans = Ask(mid+1, r, x*2+1, ql, qr);
		SegmentTree ans = (SegmentTree) {max(lans.veryMax, rans.veryMax), secmax(lans.veryMax, lans.secondMax, rans.veryMax, rans.secondMax)};
		return ans;
	}
	else if(ql <= mid) return Ask(l, mid, x*2, ql, qr);
	else return Ask(mid+1, r, x*2+1, ql, qr);
}

inline SegmentTree WayAsk(int x, int y){
	SegmentTree ans = (SegmentTree){0, 0};
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		SegmentTree tmp = Ask(1, n, 1, vertex[xTop].DFN, vertex[x].DFN);
		ans.secondMax = secmax(ans.veryMax, ans.secondMax, tmp.veryMax, tmp.secondMax);
		ans.veryMax = max(ans.veryMax, tmp.veryMax);
		x = vertex[xTop].father;
	}
	if(x == y) return ans;
	if(vertex[x].depth < vertex[y].depth) swap(x,y);
	SegmentTree tmp = Ask(1, n, 1, vertex[y].DFN+1, vertex[x].DFN);
	ans.secondMax = secmax(ans.veryMax, ans.secondMax, tmp.veryMax, tmp.secondMax);
	ans.veryMax = max(ans.veryMax, tmp.veryMax);
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++){
		int u, v, w;
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(u, v, w, 0);
	}
	sort(edge+1, edge+1+cntEdge);
	int cntMST = cntEdge;
	memset(head, 0, sizeof(head));
	for(int i=1;i<=n;i++)
		fa[i] = i;
	for(int i=1;i<=cntMST;i++){
		int cnt = 0, u = Find(edge[i].from), v = Find(edge[i].to);
		if(u != v){
			fa[u] = v;
			MST += edge[i].value;
			edge[i].used = 1;
			edge[i].nextEdge = head[edge[i].from];
			head[edge[i].from] = i;
			AddEdge(edge[i].to, edge[i].from, edge[i].value, 1);
			cnt++;
		}
		if(cnt == n-1) break;
	}
	DFS1(1);
	DFS2(1,1);
//	for(int i=1;i<=n;i++)
//		printf("%d %d %d %d %d %d %d\n", vertex[i].depth, vertex[i].father, vertex[i].heavySon, vertex[i].DFN, vertex[i].chainTop, vertex[i].subtreeSize, vertex[i].val);
	for(int i=1;i<=n;i++)
		Change(1, n, 1, vertex[i].val, vertex[i].DFN);
	for(int i=1;i<=cntEdge;i++){
		if(!edge[i].used){
			SegmentTree tmp = WayAsk(edge[i].from, edge[i].to);
			long long tmpMST = MST + edge[i].value - (tmp.veryMax == edge[i].value? tmp.secondMax : tmp.veryMax);
			if(tmpMST > MST && tmpMST < secondMST) secondMST = tmpMST;
		}
	}
	printf("%lld\n",secondMST);
	return 0;
}