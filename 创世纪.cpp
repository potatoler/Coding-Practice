#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, head[MaxN], ans, cntEdge, root, father[MaxN], f[MaxN], g[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination
pair<int,int> binding[MaxN];
int cntpair;

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

inline int Find(int x){
	if(father[x] == x) return x;
	return father[x] = Find(father[x]);
}

inline void DFS(int x){
	int res = INT_MAX;
	f[x] = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon != root) DFS(thisSon);
		f[x] += max(f[thisSon], g[thisSon]);
		res = min(res, max(f[thisSon], g[thisSon]) - f[thisSon]);
	}
	g[x] = f[x] + 1 - res;
	return;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		father[i] = i;
	for(int i=1; i<=n; i++){
		int a = Read();
		if(Find(a) != Find(i)){
			AddEdge(a, i);
			father[Find(a)] = Find(i);
		}
		else binding[++cntpair] = make_pair(a, i);
	}
	int tmp = 0;
	for(int i=1; i<=cntpair; i++){
		int a = binding[i].first, b = binding[i].second;
		DFS(a);
		root = a;
		DFS(b);
		tmp = g[b];
		g[a] = f[a] + 1;
		DFS(b);
		ans += max(tmp, f[b]);
	}
	printf("%lld", ans);
	return 0;
}