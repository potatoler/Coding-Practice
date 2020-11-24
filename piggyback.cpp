#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 40004;
int n, m, b, e, p;
int head[MaxN], cntEdge, dis[4][MaxN], ans = INT_MAX;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
typedef pair<int,int> int_pair;
priority_queue<int_pair, vector<int_pair>, greater<int_pair> > q;

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void Dijkstra(int type){
	memset(dis[type], 0x3f, sizeof(dis[type]));
	int s = type == 1? 1 : (type == 2? 2 : n);
	dis[type][s] = 0;
	q.push(make_pair(0,s));
	while(q.size()){
		int d = q.top().first, x = q.top().second;
		q.pop();
		if(d != dis[type][x]) continue;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			int z = type == 1? b : (type == 2? e : p);
			if(dis[type][y] > dis[type][x] + z){
				dis[type][y] = dis[type][x] + z;
				q.push(make_pair(dis[type][y], y));
			}
		}
	}
	return;
}

signed main(){
	b = Read(), e = Read(), p = Read(), n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(u,v), AddEdge(v,u);
	}
	Dijkstra(1);
	Dijkstra(2);
	Dijkstra(3);
	for(int i=1; i<=n; i++)
		ans = min(ans, dis[1][i] + dis[2][i] + dis[3][i]);
	printf("%lld", ans);
	return 0;
}