#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 10004*10+10004, MaxM = 2500005;
int n, m, k, s, t, dis[MaxN], head[MaxN], cntEdge;
bool visited[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxM*2];

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

inline void AddEdge(int u, int v, int w=0){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void Dijkstra(int x){
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[x] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
	q.push(make_pair(0, s));
	while(q.size()){
		int u = q.top().second;
		q.pop();
		if(!visited[u]){
			visited[u] = 1;
			for(int i = head[u]; i; i = edge[i].nextEdge){
				int v = edge[i].destination;
				if(dis[v] > dis[u] + edge[i].value){
					dis[v] = dis[u] + edge[i].value;
					q.push(make_pair(dis[v], v));
				}
			}
		}
	}
}

signed main(){
	n = Read(), m = Read(), k = Read();
	s = Read(), t = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w), AddEdge(v, u, w);
		for(int j=1; j<=k; j++){
			AddEdge(u+(j-1)*n, v+j*n);
			AddEdge(v+(j-1)*n, u+j*n);
			AddEdge(u+j*n, v+j*n, w);
			AddEdge(v+j*n, u+j*n, w);
		}
	}
	for(int i=1; i<=k; i++){
		AddEdge(t+(i-1)*n, t+i*n);
	}
	Dijkstra(s);
	printf("%lld", dis[t+k*n]);
	return 0;
}