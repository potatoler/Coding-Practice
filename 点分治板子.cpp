#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
const int MaxN = 10005;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*2];
struct Vertex{
	int subtreeSize, maxSize, distance;
	bool visited;
}vertex[MaxN];
int n, m, k, cntEdge, root, head[MaxN], sumSize, cntRoad, road[MaxN], quest[MaxN];
int exist[MaxN * MaxN], flag[MaxN * MaxN], queue[MaxN];
#define thisSon edge[i].destination

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].value = w;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
}

inline void GetRoot(int x, int fa){
	vertex[x].maxSize = 0;
	vertex[x].subtreeSize = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == fa || vertex[thisSon].visited) continue;
		GetRoot(thisSon, x);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		vertex[x].maxSize = max(vertex[x].maxSize, vertex[thisSon].subtreeSize);
	}
	vertex[x].maxSize = max(vertex[x].maxSize, sumSize - vertex[x].subtreeSize);
	if(vertex[x].maxSize < vertex[root].maxSize) root = x;
}

inline void GetDistance(int x, int fa){
	road[++cntRoad] = vertex[x].distance;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == fa || vertex[thisSon].visited) continue;
		vertex[thisSon].distance  = vertex[x].distance + edge[i].value;
		GetDistance(thisSon, x);
	}
}

inline void Calculate(int x){
	int p = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(vertex[thisSon].visited) continue;
		cntRoad = 0; 
		vertex[thisSon].distance = edge[i].value;
		GetDistance(thisSon, x);
		for(int j = cntRoad; j; j--)
			for(int k = 1; k <= m; k++)
				if(quest[k] >= road[j])	exist[k] |= flag[quest[k] - road[j]];
		for(int j = cntRoad; j; j--){
			queue[++p] = road[j];
			flag[road[j]] = 1;
		}
	}
	for(int i=1;i<=p;i++)
		flag[queue[i]] = 0;
}

inline void Devide(int x){
	vertex[x].visited = flag[0] = 1;
	Calculate(x);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(vertex[thisSon].visited) continue;
		sumSize = vertex[thisSon].subtreeSize;
		vertex[root = 0].maxSize = INT_MAX;
		GetRoot(thisSon, 0);
		Devide(root);
	}
}

signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i=1;i<n;i++){
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		AddEdge(u, v, w); AddEdge(v, u, w);
	}
	sumSize = vertex[0].maxSize = n;
	for(int i=1;i<=m;i++)
		scanf("%lld", &quest[i]);
	GetRoot(1, 0);
	Devide(root);
	for(int i=1;i<=m;i++)
		if(exist[i]) printf("AYE\n");
		else printf("NAY\n");
	return 0;
}