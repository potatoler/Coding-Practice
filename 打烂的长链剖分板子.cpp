#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<utility>
#include<vector>
#define int long long
#define ui unsigned int
using namespace std;
const int MaxN = 500005;
int n, q, head[MaxN], highBit[MaxN], cntEdge, ans, last;
ui s;
//vector<int> a;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];
struct Vertex{
	vector<int> predecessor, successor;
	int depth, maxDepth, deepSon, chainTop, father[21];
}vertex[MaxN];
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

inline ui get(ui x){
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x;
}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
}

inline void DFS1(int x){
	vertex[x].maxDepth = vertex[x].depth = vertex[vertex[x].father[0]].depth + 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father[0]) continue;
		vertex[thisSon].father[0] = x;
		for(int i=0; vertex[thisSon].father[i]; i++){
			vertex[thisSon].father[i+1] = vertex[vertex[thisSon].father[i]].father[i];
			DFS1(thisSon);
			if(vertex[thisSon].maxDepth > vertex[x].maxDepth) vertex[x].maxDepth = vertex[thisSon].maxDepth, vertex[x].deepSon = thisSon;
		}
	}
}

inline void DFS2(int x, int top){
	vertex[x].chainTop = top;
	if(x == top){
		for(int i=0, fa=x; i <= vertex[x].maxDepth-vertex[x].depth; i++)
			vertex[x].predecessor.push_back(fa), fa = vertex[fa].father[0];
		for(int i=0, fa=x; i <= vertex[x].maxDepth-vertex[x].depth; i++)
			vertex[x].successor.push_back(fa), fa = vertex[fa].deepSon;
	}
	if(vertex[x].deepSon) DFS2(vertex[x].deepSon, x);
	for(int i = head[x]; i; i = edge[i].nextEdge)
		if(thisSon ^ vertex[x].deepSon) DFS2(thisSon, thisSon);
}

inline int Query(int x, int k){
	if(!k) return x;
	x = vertex[x].father[highBit[k]];
	k -= (1<<highBit[k]);
	k -= vertex[x].depth - vertex[vertex[x].chainTop].depth;
	x = vertex[x].chainTop;
	return k>=0? vertex[x].predecessor[k] : vertex[x].successor[k];
}

signed main(){
	n = Read(), q = Read(), s = Read();
	highBit[1] = 0;
	for(int i=2; i<=n; i++)
		highBit[i] = highBit[i>>1] + 1;
	int root = 0;
	for(int i=1; i<=n; i++){
		int fa = Read();
		if(fa == 0) root = i;
		AddEdge(fa, i), AddEdge(i, fa);
		vertex[i].father[0] = fa;
	}
	DFS1(1);
	DFS2(1, 1);
	for(int i=1; i<=q; i++){
		int x = ((get(s) ^ last) % n) + 1;
		int k = ((get(s) ^ last) % vertex[x].depth);
		last = Query(x, k);
		ans ^= i * last;
	}
	printf("%lld\n",ans);
}