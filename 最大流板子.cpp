#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 5003;
int n, m, s, t, head[MaxN], cntEdge = 1;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN * 2];
int dis[MaxN], pre[MaxN], ans, exist[MaxN][MaxN];
bool visited[MaxN];

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
	cntEdge++;
	edge[cntEdge].destination = u;
	edge[cntEdge].nextEdge = head[v];
	edge[cntEdge].value = 0;
	head[v] = cntEdge;
	return;
}

inline int BFS(){
	for(int i=1; i<=n; i++)
		visited[i] = false;
	queue<int> q;
	q.push(s);
	visited[s] = true;
	dis[s] = INT_MAX;
	while(q.size()) {
		int x=q.front();
		q.pop();
		for(int i = head[x]; i; i = edge[i].nextEdge){
			if(edge[i].value == 0) continue; 
			int des = edge[i].destination;
			if(visited[des] == true) continue;
			dis[des] = min(dis[x], edge[i].value);
			pre[des] = i; 
			q.push(des);
			visited[des] = 1;
			if(des == t) return 1;
		}
	}
	return 0;
}

inline void Update(){
	int x = t;
	while(x != s){
		int y = pre[x];
		edge[y].value -= dis[t];
		edge[y^1].value += dis[t];
		x = edge[y^1].destination;
	}
	ans += dis[t];
	return;
}

signed main(){
	n = Read(), m = Read(), s = Read(), t = Read();
	for(int i=1; i<=m ;i++){
		int u = Read(), v = Read(), w = Read();
		if(!exist[u][v]){
			AddEdge(u, v, w);
			exist[u][v] = cntEdge;
		}
		else edge[exist[u][v]-1].value += w;
	}
	while(BFS()){
//		for(int i=1; i<=n; i++)
//			printf("%lld ", pre[i]);
//		printf("\n");
		Update();
	}
	printf("%lld", ans);
	return 0;
}