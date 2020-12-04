#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<map>
#include<vector>
#include<queue>
//#define int long long
using namespace std;
const int MaxN = 1000006;
int n, m, k, head[MaxN], cntEdge, dis[MaxN];
struct Edge{
	int from, to, value, nextEdge;
}edge[MaxN*2];
struct Node{
	int serial, value;
	bool operator < (const Node &y) const {
		return value < y.value;
	}
}node[MaxN];
typedef pair<int,int> int_pair;
map<int_pair,bool> mp;

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
	edge[cntEdge].from = u;
	edge[cntEdge].to = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void Dijkstra(){
	dis[1] = 0, dis[0] = INT_MAX;
	priority_queue<int_pair, vector<int_pair>, greater<int_pair> > q;
	q.push({0,1});
	while(q.size()){
		int_pair tp = q.top();
		q.pop();
		int dist = tp.first, pos = tp.second;
		for(int i = head[pos]; ~i; i = edge[i].nextEdge){
			int y = edge[i].to;
			if(dis[y] > dist + edge[i].value){
				dis[y] = dist + edge[i].value;
				q.push({dis[y],y});
			}
		}
	}
}

signed main(){
//	freopen("C.in", "r", stdin);
//	freopen("C.out", "w", stdout);
	memset(head, -1, sizeof(head));
	n = Read(), m = Read(), k = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u,v,w);
		AddEdge(v,u,w);
		mp[{u,v}] = true;
	}
	for(int i=1; i<=n; i++){
		node[i].value = Read();
		node[i].serial = i;
		dis[i] = INT_MAX;
	}
	sort(node+1, node+1+n);
	if(k == -1){
		for(int i=1; i<n; i++){
			int u = node[i].serial, v = node[i+1].serial;
			if(mp[{u,v}]) continue;
			AddEdge(u, v, abs(node[i].value + k * node[i+1].value));
			AddEdge(v, u, abs(node[i].value + k * node[i+1].value));
			mp[{u,v}] = true;
		}
	}
	else if(k == 1){
		for(int i=1; i<=n; i++){
			AddEdge(node[i].serial, 0, node[i].value);
			AddEdge(0, node[i].serial, node[i].value);
		}
	}
	Dijkstra();
	printf("%d", dis[n]);
	return 0;
}