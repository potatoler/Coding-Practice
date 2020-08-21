#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long 
using namespace std;
const int MaxN = 202 * 2;
int n, cntEdge, ans, head[MaxN * MaxN], match[MaxN], visited[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN * MaxN];

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

inline int DFS(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int des = edge[i].destination;
		if(!visited[des]){
			visited[des] = 1;
			if(!match[des] || DFS(match[des])){
				match[des] = x;
				return 1;
			}
		}
	}
	return 0;
}

inline void Reset(){
	ans = 0;
	for(int i=1; i<=cntEdge; i++)
		edge[i].destination = edge[i].nextEdge = head[i] = 0;
//	cntEdge = 1;
	for(int i=1; i<=2*n; i++)
		match[i] = 0;
}

signed main(){
	int T = Read();
	while(T--){
		Reset();
		n = Read();
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++){
				int x = Read();
				if(x) AddEdge(i, j+n);
			}
		for(int i=1; i<=n; i++){
			memset(visited, 0, sizeof(visited));
			ans += DFS(i);
		}
		if(ans >= n) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}