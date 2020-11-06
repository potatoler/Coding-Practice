#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#include<queue>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005, MaxM = 200005;
int n, m, s, head[MaxN], cntEdge, dis[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxM];
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

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void Dijkstra(){
//	for(int i=1; i<=n; i++)
//		dis[i] = INT_MAX;
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0;
	q.push(make_pair(0, s));
	while(q.size()){
		int d = q.top().first, x = q.top().second;
		q.pop();
		if(d != dis[x]) continue;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination, z = edge[i].value;
			if(dis[y] > dis[x] + z){
				dis[y] = dis[x] + z;
				q.push(make_pair(dis[y], y));
			}
		}
	}
	return;
}

signed main(){
	n = Read(), m = Read(), s = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
	}
	Dijkstra();
	for(int i=1; i<=n; i++)
		printf("%lld ", dis[i]);
	return 0;
}