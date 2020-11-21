#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1000006, MaxM = 2000006, Mod = 1000000007;
int n, m, dis[MaxN];
int head[MaxN], cntEdge;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxM];
bool visited[MaxN];
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

inline void Dijkstra(int s){
	dis[s] = 0;
	q.push(make_pair(0, s));
	while(q.size()){
		int d = q.top().first, x = q.top().second;
		q.pop();
		if(d != dis[x]) continue;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination, z = edge[i].value;
//			printf("%lld %lld %lld\n", x, y, (dis[x]<<1) + z);
			if(dis[y] > ((dis[x]<<1) + z) % Mod){
				dis[y] = ((dis[x]<<1) + z) % Mod;
				q.push(make_pair(dis[y], y));
			}
		}
	}
	return;
}


signed main(){
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u,v,w);
	}
	for(int i=0; i<MaxN; i++)
		dis[i] = Mod;
	Dijkstra(1);
	for(int i=2; i<=n; i++){
		if(dis[i] == Mod) printf("-1 ");
		else printf("%lld ", dis[i] % Mod);
	}
	return 0;
}