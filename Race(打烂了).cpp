#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
const int MaxN = 200005, MaxK = 1000010;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*2];
int maxSize[MaxN], subtreeSize[MaxN], head[MaxN], depth[MaxN], val[MaxN], pathValue[MaxN], pathLenth[MaxN], queue[MaxN], minLenth[MaxK];
bool vis[MaxN];
int n, k, cntEdge, ans = INT_MAX, sumSize, root;

#define thisSon edge[i].destination
#define cntPath pathValue[0]
#define top queue[0]

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].value = w;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
}

inline void GetRoot(int x, int fa){
	subtreeSize[x] = 1;
	maxSize[x] = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == fa || vis[thisSon]) continue;
		GetRoot(thisSon, x);
		subtreeSize[x] += subtreeSize[thisSon];
		maxSize[x] = max(maxSize[x], subtreeSize[thisSon]);
	}
	maxSize[x] = max(maxSize[x], sumSize - subtreeSize[x]);
	if(maxSize[x] < maxSize[root]) root = x;
}

inline void GetDistance(int x, int fa){
	pathValue[++cntPath] = val[x];
	pathLenth[cntPath] = depth[x];
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == fa || vis[thisSon]) continue;
		depth[thisSon] = depth[x] + 1;
		val[thisSon] = val[x] + edge[i].value;
		GetDistance(thisSon, x);
	}
}

inline void Calculate(int x){
	top = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(vis[thisSon]) continue;
		val[thisSon] = edge[i].value;
		depth[thisSon] = 1;
		cntPath = pathLenth[0] = 0;
		GetDistance(thisSon, x);
		for(int j = 1; j <= cntPath; j++){
			if(k - pathValue[j] < 0) continue;
			if(minLenth[k - pathValue[j]] < INT_MAX) ans = min(ans, pathLenth[j] + minLenth[k - pathValue[j]]);
		}	
		for(int j = 1; j <= cntPath; j++){
			if(pathValue[j] <= k){
				minLenth[pathValue[j]] = min(minLenth[pathValue[j]], depth[j]);
				queue[++top] = pathValue[j];
			}
		}
	}
	for(int i = 1; i <= top; i++)
		minLenth[queue[i]] = INT_MAX;
}

inline void Solve(int x){
	vis[x] = true;
	minLenth[0] = 0;
	Calculate(x);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(vis[thisSon]) continue;
		maxSize[root = 0] = INT_MAX;
		sumSize = subtreeSize[thisSon];
		GetRoot(thisSon, 0);
		Solve(root);
	}
}

signed main(){
	scanf("%lld%lld", &n, &k);
	for(int i=1;i<=k;i++)
		minLenth[i] = INT_MAX;
	for(int i=1;i<n;i++){
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	maxSize[root] = sumSize = n;
	GetRoot(1, 0);
	Solve(root);
	if(ans <= n) printf("%lld\n", ans);
	else printf("-1\n");
	return 0;
}