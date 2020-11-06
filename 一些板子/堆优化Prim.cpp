#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#include<utility>
#include<vector>
#define int long long
using namespace std;
typedef pair<int,int> int_pair;
const int MaxN = 5003, MaxM = 200005;
int n, m, head[MaxN], cntEdge, dis[MaxN], ans, tot;
bool visited[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxM*2];
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

inline void Prim(){
	for(int i=2; i<=n; i++)
		dis[i] = INT_MAX;
	q.push(make_pair(0, 1));	
	while(q.size() && tot < n){
		int disx = q.top().first, x = q.top().second;
		q.pop();
		if(visited[x]) continue;
		tot++;
		ans += disx;
		visited[x] = true;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination, z = edge[i].value;
			if(z < dis[y]){
				dis[y] = z;
				q.push(make_pair(dis[y], y));
			}
		}
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	Prim();
	if(tot == n) printf("%lld", ans);
	return 0;
}