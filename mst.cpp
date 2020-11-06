#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 71, MaxM = 202;
int n, m, a, b, head[MaxN], cntEdge, father[MaxN], size[MaxN], cntBlock;
int serial[MaxN], dis[1<<(MaxN/4)][MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxM*2];
struct Tri_Pair{
	int bit, pos, dis;
	bool operator < (const Tri_Pair &y) const{
		return dis > y.dis;
	}
};
priority_queue<Tri_Pair> q;

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

inline int Find(int x){
	return father[x] == x ? x : father[x] = Find(father[x]);
}

inline void Merge(int x, int y){
	x = Find(x), y = Find(y);
	if(x != y){
		size[x] += size[y];
		father[y] = x;
	}
	return;
}

inline void Dijkstra(int s){
	q.push((Tri_Pair){0,s,0});
	memset(dis, 0x3f, sizeof(dis));
	dis[0][s] = 0;
	while(q.size()){
		Tri_Pair cur = q.top();
		q.pop();
		if(cur.dis != dis[cur.bit][cur.pos]) continue;
		for(int i = head[cur.pos]; i; i = edge[i].nextEdge){
			int v = edge[i].destination, w = edge[i].value;
			if(serial[v] && (cur.bit>>(serial[v]-1) & 1 || (w == b && serial[cur.pos] == serial[v]))) continue;
			int bit = cur.bit | (serial[cur.pos] && serial[cur.pos] == serial[v]? 0 : 1<<(serial[cur.pos]-1));
			if(dis[bit][v] > cur.dis + w){
				dis[bit][v] = cur.dis + w;
				q.push((Tri_Pair){bit, v, dis[bit][v]});
			}
		}
	}
	return;
}

signed main(){
	freopen("mst.in", "r", stdin);
	freopen("mst.out", "w", stdout);
	n = Read(), m = Read(), a = Read(), b = Read();
	for(int i=1; i<=n; i++){
		father[i] = i;
		size[i] = 1;
	}
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
		if(w == a) Merge(u, v);
	}
	for(int i=1; i<=n; i++){
		int fa = Find(i);
		if(size[fa] <= 3) continue;
		if(!serial[fa]) serial[fa] = ++cntBlock;
		serial[i] = serial[fa];
	}
//	for(int i=1; i<=n; i++)
//		printf("%lld ", serial[i]);
	Dijkstra(1);
	for(int i=1; i<=n; i++){
		int ans = 0x3f3f3f3f;
		for(int j=0; j<(1<<cntBlock); j++)
//			printf("%lld\n", dis[j][i]),
			ans = min(ans, dis[j][i]);
		printf("%lld ", ans);
	}
	return 0;
}