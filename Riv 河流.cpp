#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 102;
int n, k, w[MaxN], d[MaxN], head[MaxN], cntEdge, f[MaxN][MaxN][MaxN][2], stack[MaxN], top, dis[MaxN];
bool visited[MaxN];
struct Edge{
	int destination, value, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination

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
	edge[cntEdge].value = w;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS(int x){
	stack[++top] = x;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(visited[thisSon]) continue;
		visited[thisSon] = true;
		dis[thisSon] = dis[x] + edge[i].value;
		DFS(thisSon);
		for(int j=top; j>=1; j--){
			int father = stack[j];
			for(int subk = k; subk>=0; subk--){
				f[x][father][subk][1] += f[thisSon][x][0][0];
				f[x][father][subk][0] += f[thisSon][father][0][0];
				for(int l=subk; l>=0; l--){
					f[x][father][subk][0] = min(f[x][father][subk][0], f[thisSon][father][l][0] + f[x][father][subk-l][0]);
					f[x][father][subk][1] = min(f[x][father][subk][1], f[thisSon][x][l][0] + f[x][father][subk-l][1]);
				}
			}
		}
	}
	for(int i=1; i<=top; i++){
		int father = stack[i];
		for(int j=k; j>=0; j--){
			if(j >= 1) f[x][father][j][0] = min(f[x][father][j][0] + w[x] * (dis[x]-dis[father]), f[x][father][j-1][1]);
			else f[x][father][j][0] += w[x] * (dis[x]-dis[father]);
		}
	}
	top--;
	return;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		w[i] = Read();
		int father = Read();
		d[i] = Read();
		AddEdge(father, i, d[i]);
	}
	visited[0] = 1;
	DFS(0);
	printf("%lld", f[0][0][k][0]);
	return 0;
}