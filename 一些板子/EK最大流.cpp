#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
using namespace std;
const int MaxN = 1003, MaxM = 10004;
int n, m, s, t, head[MaxN], cntEdge = -1;
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM*2];
queue<int> q;
int dis[MaxN], pre[MaxN];
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

inline void AddEdge(int u, int v, int c){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].capacity = c;
	head[u] = cntEdge;
	return;
}

inline bool BFS(){
	while(q.size()) q.pop();
	memset(visited, false, sizeof(visited));
	q.push(s), visited[s] = true, dis[s] = INT_MAX;
	while(q.size()){
		int x = q.front();
		q.pop();
		for(int i = head[x]; ~i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(!visited[y] && edge[i].capacity){
				visited[y] = true;
				dis[y] = min(dis[x], edge[i].capacity);
				pre[y] = i;
				if(y == t) return true;
				q.push(y);
			}
		}
	}
	return false;
}

inline int EK(){
	int res = 0;
	while(BFS()){
		res += dis[t];
		for(int i = t; i != s; i = edge[pre[i]^1].destination){
			edge[pre[i]].capacity -= dis[t];
			edge[pre[i]^1].capacity += dis[t];
		}
	}
	return res;
}

signed main(){
	n = Read(), m = Read(), s = Read(), t = Read();
	memset(head, -1, sizeof(head)); // important
	while(m--){
		int u = Read(), v = Read(), c = Read();
		AddEdge(u, v, c);
		AddEdge(v, u, 0);
	}
	for(int x=1; x<=n; x++){
		for(int i = head[x]; ~i; i = edge[i].nextEdge)
			printf("%d ", edge[i].destination);
		printf("\n");
	}
	printf("%d\n", EK());
	return 0;
}