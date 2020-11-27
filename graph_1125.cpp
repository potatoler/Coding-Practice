#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 402, MaxM = MaxN*MaxN/2;
int n, m, s, t;
int head[MaxN], cntEdge, ans[MaxM], depth[MaxN];
struct Edge{
	int destination, nextEdge, serial;
}edge[MaxM*2];

inline void AddEdge(int u, int v, int id){
	cntEdge++;
	edge[cntEdge].serial = id;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

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

inline void BFS(){
	queue<int> q;
	q.push(s);
	depth[s] = 1;
	while(q.size()){
		int x = q.front();
		q.pop();
		if(depth[x] == depth[t]) break;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(!depth[y]){
				depth[y] = depth[x]+1;
				ans[edge[i].serial] = depth[x];
				q.push(y);
			}
			else if(depth[y] == depth[x]+1) ans[edge[i].serial] = depth[x];
		}
	}
}

signed main(){
//	freopen("graph.in", "r", stdin);
//	freopen("graph.out", "w", stdout);
	n = Read(), m = Read();
	s = Read(), t = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(u,v,i);
		AddEdge(v,u,i);
	}
	BFS();
	printf("%lld\n", depth[t]-1);
	for(int i=1; i<=m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}