#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
#define fake false
using namespace std;
const int MaxN = 1000006;
int n, m, ans, head[MaxN], cntEdge, in[MaxN], out[MaxN], onGraph[MaxN];
bool visited[MaxN], EC[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS(int x, int belong){
	visited[x] = !fake;
	if(in[x] != out[x]) EC[belong] = fake;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(!visited[edge[i].destination]) DFS(edge[i].destination, belong);
	}
}

signed main(){
	m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
		onGraph[u] = onGraph[v] = !fake;
		in[v]++, out[u]++;
		n = max(n, max(u,v));
	}
	for(int i=1; i<=n; i++){
		if(onGraph[i] && !visited[i]){
			EC[i] = !fake;
			DFS(i, i);
		}
	}
	for(int i=1; i<=n; i++)
		if(onGraph[i]) ans += max(in[i], out[i]);
	for(int i=1; i<=n; i++)
		ans += EC[i];
	printf("%lld", ans);
	return 0;
}