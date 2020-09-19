#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1003 * 1003;
int n, m, a, b, c, head[MaxN], cntEdge, w[MaxN];
int tot[MaxN], dist[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN];
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

inline int Serial(int x, int y){
	return (x-1) * m + y;
}

inline void Dijkstra(int x, int y){
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			dist[Serial(i, j)] = LLONG_MAX;
	priority_queue< pair<int, pair<int,int> > > q;
	memset(visited, false, sizeof(visited));
	dist[Serial(x, y)] = w[Serial(x, y)];
	q.push(make_pair(w[Serial(x,y)], make_pair(x,y)));
	while(!q.empty()){
		int xx = q.top().second.first, yy = q.top().second.second, u = Serial(xx, yy);
		q.pop();
		if(visited[u]) continue;
		visited[u] = true;
		int v;
		if(xx != 1){
			v = Serial(xx-1, yy);
			if(dist[v] > dist[u] + w[v]){
				dist[v] = dist[u] + w[v];
				pair<int,int> tmp;
				if(!visited[v]) q.push(make_pair(-dist[v], make_pair(xx-1, yy)));
			}
		}
		if(xx != n){
			v = Serial(xx+1, yy);
			if(dist[v] > dist[u] + w[v]){
				dist[v] = dist[u] + w[v];
				if(!visited[v]) q.push(make_pair(-dist[v], make_pair(xx+1, yy)));
			}
		}
		if(yy != 1){
			v = Serial(xx, yy-1);
			if(dist[v] > dist[u] + w[v]){
				dist[v] = dist[u] + w[v];
				if(!visited[v]) q.push(make_pair(-dist[v], make_pair(xx, yy-1)));
			}
		}
		if(yy != m){
			v = Serial(xx, yy+1);
			if(dist[v] > dist[u] + w[v]){
				dist[v] = dist[u] + w[v];
				if(!visited[v]) q.push(make_pair(-dist[v], make_pair(xx, yy+1)));
			}
		}
	}
}

signed main(){
	n = Read(), m = Read(), a = Read(), b = Read(), c = Read();
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			w[Serial(i, j)] = Read();
	Dijkstra(n, a);
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			tot[Serial(i, j)] += dist[Serial(i, j)];
	Dijkstra(1, b);
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			tot[Serial(i, j)] += dist[Serial(i, j)];
	Dijkstra(1, c);
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			tot[Serial(i, j)] += dist[Serial(i, j)];
	int ans = LLONG_MAX;
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			ans = min(ans, tot[Serial(i, j)]-2*w[Serial(i, j)]);
	printf("%lld", ans);
	return 0;
}