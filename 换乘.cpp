#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#include<map>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, m, ed, head[MaxN], cntEdge, dis[MaxN];
bool visited[MaxN];
struct Edge{
	int destination, nextEdge, value;
	bool operator < (const Edge &b) const{
		return value > b.value;
	}
}edge[MaxN*2];
map<int, int> mp[MaxN];

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

inline void Dijkstra(int s, int e){
	priority_queue<Edge> q;
	for(int i=0; i<MaxN; i++)
		dis[i] = INT_MAX, visited[i] = false;
	dis[s] = 0;
	q.push(Edge{s,0,0});
	while(q.size()){
		Edge x = q.top();
		q.pop();
		if(visited[x.destination]) continue;
		visited[x.destination] = true;
		for(int i = head[x.destination]; i; i = edge[i].nextEdge){
			int des = edge[i].destination;
			if(dis[des] > dis[x.destination] + edge[i].value){
				dis[des] = dis[x.destination] + edge[i].value;
				q.push(Edge{des, 0, dis[des]});
			}
		}
	}
	return;
}

inline int Serial(int x, int y){
	if(!mp[x][y]) mp[x][y] = ++n;
	return mp[x][y];
}

signed main(){
	ed = n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), c = Read();
		int uc = Serial(u, c), vc = Serial(v, c);
		AddEdge(uc, vc, 0);
		AddEdge(vc, uc, 0);
		AddEdge(u, uc, 1);
		AddEdge(uc, u, 1);
		AddEdge(v, vc, 1);
		AddEdge(vc, v, 1);
	}
	Dijkstra(1, ed);
	int ans = dis[ed] == INT_MAX? -1 : dis[ed]/2;
	printf("%lld", ans);
}