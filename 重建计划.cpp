#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
const double eps = 1e-4;
int N, L, U, cntEdge, cntDFN, serial[MaxN];
double dep[MaxN], ans, newValue[MaxN * 2];
struct Edge{
	int destination, nextEdge;
	double value;
}edge[MaxN * 2];
struct Vertex{
	int depth, maxLength, longSon, father, chainTop, head, DFN;
	double dist;
}vertex[MaxN];
struct SegmentTree{
	int l, r;
	double maxLength;
}segment[MaxN * 8];

#define itsFather vertex[x].father
#define thisSon edge[i].destination

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
	edge[cntEdge].value = w;
	vertex[u].head = cntEdge;
	return;
}

inline void DFS1(int x){
	vertex[x].depth = vertex[x].maxLength = vertex[itsFather].depth + 1;
	for(int i = vertex[x].head; i; i = edge[i].nextEdge){
		if(thisSon == itsFather) continue;
		vertex[thisSon].father = x;
		DFS1(thisSon);
		vertex[x].maxLength = max(vertex[x].maxLength, vertex[thisSon].maxLength);
		if(vertex[thisSon].maxLength > vertex[vertex[x].longSon].maxLength) vertex[x].longSon = thisSon;
	}
}

inline void DFS2(int x, int top){
	vertex[x].DFN = ++cntDFN;
//	serial[vertex[x].DFN] = x;
	vertex[x].chainTop = top;
	if(!vertex[x].longSon) return;
	DFS2(vertex[x].longSon, top);
	for(int i = vertex[x].head; i; i = edge[i].nextEdge){
		if(thisSon == itsFather || thisSon == vertex[x].longSon) continue;
		DFS2(thisSon, thisSon);
	}
}

inline void Build(int x, int l, int r){
	segment[x].l = l, segment[x].r = r;
	segment[x].maxLength = -LLONG_MAX;
	if(l == r){
		serial[l] = x;
		return;
	}
	int mid = (l + r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
}

inline void Update(int x){
	segment[x].maxLength = max(segment[x*2].maxLength, segment[x*2+1].maxLength);
	return;
}

inline void Change(int x, int pos, double val){
	if(segment[x].l == segment[x].r){
		segment[x].maxLength = max(segment[x].maxLength, val);
		return;
	}
	int mid = (segment[x].l + segment[x].r) / 2;
	if(pos <= mid) Change(x*2, pos, val);
	else Change(x*2+1, pos, val);
	Update(x);
}

inline double Query(int x, int ql, int qr){
	if(ql > qr) return -LLONG_MAX;
	if(ql <= segment[x].l && segment[x].r <= qr) return segment[x].maxLength;
	int mid = (segment[x].l + segment[x].r) / 2;
	double res = -LLONG_MAX;
	if(ql <= mid) res = max(res, Query(x*2, ql, qr));
	if(qr > mid) res = max(res, Query(x*2+1, ql, qr));
	return res;
}

inline void DP(int x){
	Change(1, vertex[x].DFN, vertex[x].dist);
	for(int i = vertex[x].head; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].longSon){
			vertex[vertex[x].longSon].dist = vertex[x].dist + newValue[i];
			DP(vertex[x].longSon);
		}
	}
	for(int i = vertex[x].head; i; i = edge[i].nextEdge){
		if(thisSon == itsFather || thisSon == vertex[x].longSon) continue;
		vertex[thisSon].dist = vertex[x].dist + newValue[i];
		DP(thisSon);
		for(int j=1; j <= vertex[thisSon].maxLength - vertex[x].depth; j++){
			dep[j] = segment[serial[vertex[thisSon].DFN+j-1]].maxLength;
			if(j <= U){
				ans = max(ans, Query(1, max(vertex[x].DFN, vertex[x].DFN+L-j), min(vertex[x].DFN + vertex[x].maxLength - vertex[x].depth, vertex[x].DFN + U - j)) + dep[j] - 2 * vertex[x].dist);
			}
		}
		for(int j=1; j <= vertex[thisSon].maxLength - vertex[x].depth; j++)
			Change(1, vertex[x].DFN + j, dep[j]);
	}
	ans=max(ans,Query(1,vertex[x].DFN+L,min(vertex[x].DFN+vertex[x].maxLength-vertex[x].depth,vertex[x].DFN+U))-vertex[x].dist);
}

signed main(){
//	freopen("test.in", "r", stdin);
//	freopen("test.out", "w", stdout);
	N = Read(), L = Read(), U = Read();
	for(int i=1; i<N; i++){
		int x = Read(), y = Read(), z = Read();
		AddEdge(x, y, z);
		AddEdge(y, x, z);
	}
	double l = 0, r = 1000000;
	DFS1(1);
	DFS2(1, 1);
//	for(int i=1; i<=N; i++)
//		printf("%lld %lld %lld %lld %lld\n", vertex[i].depth, vertex[i].maxLength, vertex[i].father, vertex[i].DFN, vertex[i].longSon);
	while(r - l > eps){
		double mid = (l + r) / 2;
		for(int i=1; i<=cntEdge; i++)
			newValue[i] = edge[i].value - mid;
		ans = -LLONG_MAX;
		vertex[1].dist = 0;
		Build(1, 1, N);
//		for(int i=1; i<=N; is+)
//			printf("%lld ", serial[i]);
//		printf("\n");
		DP(1);
//		for(int i=1; i<=N; i++)
//			printf("%.3lf ", vertex[i].dist);
//		printf("\n");
//		printf("%.3lf\n", ans);
		if(ans < 0) r = mid;
		else l = mid;
	}
	printf("%.3lf", l);
	return 0;
	
}