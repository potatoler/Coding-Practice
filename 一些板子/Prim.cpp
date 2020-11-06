#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 5003, MaxM = 200005;
int n, m, head[MaxN], cntEdge, dis[MaxN], ans, tot=1, cur=1;
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
	for(int i = head[1]; i; i = edge[i].nextEdge){
		int y = edge[i].destination, z = edge[i].value;
		dis[y] = min(dis[y], z);
	}
	while(tot<n){
		int mn = INT_MAX;
		visited[cur] = true;
		for(int i=1; i<=n; i++){
			if(!visited[i] && mn > dis[i]){
				mn = dis[i];
				cur = i;
			}
		}
		ans += mn;
		for(int i = head[cur]; i; i = edge[i].nextEdge){
			int y = edge[i].destination, z = edge[i].value;
			if(dis[y] > z && !visited[y]) dis[y] = z;
		}
		tot++;
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
	printf("%lld", ans);
	return 0;
}