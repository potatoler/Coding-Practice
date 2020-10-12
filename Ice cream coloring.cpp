#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int MaxN = 300005;
int n, m, head[MaxN], cntEdge, ans, colour[MaxN];
struct Edge{
	int destination, nextEdge;
	#define thisSon edge[i].destination
}edge[MaxN*2];
vector<int> ice[MaxN];
map<int,bool> visited;
//bool visited[MaxN];

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

inline void DFS(int x, int father){
//	memset(visited, false, sizeof(visited));
	visited.clear();
	for(int i=0; i<ice[x].size(); i++)
		if(colour[ice[x][i]]) visited[colour[ice[x][i]]] = true;
	int cnt = 1;
	for(int i=0; i<ice[x].size(); i++){
		if(colour[ice[x][i]]) continue;
		while(visited[cnt]) cnt++;
		colour[ice[x][i]] = cnt;
		visited[cnt] = true;
	}
	for(int i = head[x]; i; i = edge[i].nextEdge)
		if(thisSon != father) DFS(thisSon, x);
	return; 
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		int s = Read();
//		ans = max(ans, s);
		while(s--){
			int type = Read();
			ice[i].push_back(type);
		}
	}
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
	}
	DFS(1,0);
	for(int i=1; i<=m; i++){
		if(!colour[i]) colour[i] = 1;
		ans = max(ans, colour[i]);
	}
	printf("%d\n", ans);
	for(int i=1; i<=m; i++)
		printf("%d ", colour[i]);
	return 0;
}