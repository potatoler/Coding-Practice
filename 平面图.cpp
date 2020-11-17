#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 2003;
int n, m, cntEdge, tot, ans;
int x[MaxN], y[MaxN], father[MaxN];
int cost[15];
vector<int> block[15];

class Edge{
	public:
	int from, to, value;
	
	Edge() = default;
	Edge(int u, int v){
		from = u, to = v;
		value = (x[u]-x[v]) * (x[u]-x[v]) + (y[u]-y[v]) * (y[u]-y[v]);
	}
	
	inline bool operator < (const Edge &b) const {
		return value < b.value;
	}
}graph[MaxN*MaxN], MST[MaxN];

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

inline int Find(int a){
	return father[a] == a? a : father[a] = Find(father[a]);
}

inline void Init(){
	for(int i=1; i<=n; i++)
		father[i] = i;
	tot = 0;
	for(int i=1; i<=cntEdge; i++){
		if(Find(father[graph[i].from]) == Find(father[graph[i].to])) continue;
		father[Find(father[graph[i].from])] = Find(father[graph[i].to]);
		ans += graph[i].value;
		MST[++tot] = graph[i];
		if(tot == n-1) break;
	}
	return;
}

inline void Solve(int s){
	int sum = 0;
	for(int i=1; i<=n; i++)
		father[i] = i;
	for(int i=1; i<=m; i++){
		if(!(s & (1<<(i-1)))) continue;
		sum += cost[i];
		for(int j=0; j<block[i].size(); j++){
			if(Find(block[i][j]) != Find(block[i][0])) father[Find(block[i][j])] = Find(block[i][0]);
		}
	}
	for(int i=1; i<n; i++){
		if(Find(father[MST[i].from]) == Find(father[MST[i].to])) continue;
		father[Find(father[MST[i].from])] = Find(father[MST[i].to]);
		sum += MST[i].value;
	}
	ans = min(ans, sum);
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		x[i] = Read(), y[i] = Read();
	for(int i=1; i<n; i++)
		for(int j=i+1; j<=n; j++)
			graph[++cntEdge] = Edge(i,j);
	sort(graph+1, graph+1+cntEdge);
	Init();
	for(int i=1; i<=m; i++){
		int k = Read();
		cost[i] = Read();
		while(k--){
			int ver = Read();
			block[i].push_back(ver);
		}
	}
	for(int i=1; i<(1<<m); i++)
		Solve(i);
	printf("%lld", ans);
	return 0;
}
