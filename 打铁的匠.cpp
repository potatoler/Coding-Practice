#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, q, c, k, head[MaxN], cntEdge, serial[MaxN], cntDFN;
struct Vertex{
	int DFN, subtreeSize, costSum;
}vertex[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN];
#define thisSon edge[i].destination
#define thisValue edge[i].value
struct SegmentTree{
	int l, r, max, sec, min, num;
	long long sum;
}tree[MaxN*4];
#define thisTree tree[x]
#define leftSon tree[x<<1]
#define rightSon tree[x<<1|1]

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
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void DFS(int x){
	vertex[x].DFN = ++cntDFN;
	serial[cntDFN] = x;
	vertex[x].subtreeSize = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		vertex[thisSon].costSum = vertex[x].costSum + thisValue;
		DFS(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
	}
}

inline void Update(int x){
	thisTree.sum = leftSon.sum + rightSon.sum;
	thisTree.max = max(leftSon.max, rightSon.max);
	thisTree.min = min(leftSon.min, rightSon.min);
	if(leftSon.max == rightSon.max){
		thisTree.num = leftSon.num + rightSon.num;
		thisTree.sec = max(leftSon.sec, rightSon.sec);
	}
	else{
		if(leftSon.max > rightSon.max) thisTree.num = leftSon.num;
		else thisTree.num = rightSon.num;
		thisTree.sec = max(leftSon.sec, rightSon.sec);
		thisTree.sec = max(thisTree.sec, min(leftSon.max, rightSon.max));
	}
	return;
}

inline void Build(int x, int l, int r){
	thisTree.l = l, thisTree.r = r;
	if(l == r){
		thisTree.sum = vertex[serial[l]].costSum;
		thisTree.max = thisTree.min = thisTree.sum;
		thisTree.num = 1;
		thisTree.sec = -1;
		return;
	}
	int mid = (l+r) >> 1;
	Build(x<<1, l, mid), Build(x<<1|1, mid+1, r);
	Update(x);
	return;
}

inline int Query(int x, int ql, int qr){
	if(ql <= thisTree.l && thisTree.r <= qr){
		if(thisTree.max < c + k) return 0ll;
		if(thisTree.sec < c + k) return (thisTree.max - c) * thisTree.num;
		if(thisTree.min >= c + k) return thisTree.sum - c * (thisTree.r - thisTree.l + 1);
	}
	int mid = (thisTree.l + thisTree.r) >> 1;
	int ans = 0;
	if(ql <= mid) ans += Query(x<<1, ql, qr);
	if(qr > mid) ans += Query(x<<1|1, ql, qr);
//	if(qr <= mid) return Query(x<<1, ql, qr);
//	else if(ql > mid) return Query(x<<1|1, ql, qr);
//	else return Query(x<<1, ql, mid) + Query(x<<1|1, mid+1, qr);
	return ans;
}

signed main(){
//	freopen("tree.in", "r", stdin);
//	freopen("tree.out", "w", stdout);
	n = Read();
	for(int i=2; i<=n; i++){
		int fa = Read(), w = Read();
		AddEdge(fa, i, w);
	}
	DFS(1);
	Build(1, 1, n);
//	for(int i=1; i<=n*4; i++)
//		printf("%lld ", tree[i].sec);
	q = Read();
	while(q--){
		int u = Read();
		k = Read();
		int ql = vertex[u].DFN, qr = vertex[u].DFN + vertex[u].subtreeSize - 1;
		c = vertex[u].costSum;
		printf("%lld\n", Query(1, ql, qr));
	}
	return 0;
}