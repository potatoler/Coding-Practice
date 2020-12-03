#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, head[MaxN], cntEdge;
double q[MaxN], ans, f[MaxN], g[MaxN];
struct Edge{
	int destination, nextEdge;
	double probability;
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

inline void AddEdge(int u, int v, double p){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].probability = p;
	head[u] = cntEdge;
	return;
}

inline void DFS1(int x, int father){
	f[x] = 1.0 - q[x];
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		double p = edge[i].probability;
		if(y == father) continue;
		DFS1(y,x);
		f[x] = f[x] * (1-p + p*f[y]);
	}
	return;
}

inline void DFS2(int x, int father, int serial){
	if(x == 1) g[x] = f[x];
	else{
		double p = edge[serial].probability;
		double contribute = g[father] / (1-p + p*f[x]);
		g[x] = f[x] * (1-p + p*contribute);
	}
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == father) continue;
		DFS2(y,x,i);
	}
	return;
}

signed main(){
	n = Read();
	for(int i=1; i<n; i++){
		int a = Read(), b = Read();
		double p;
		scanf("%lf", &p);
		p = p * 0.01;
		AddEdge(a,b,p);
		AddEdge(b,a,p);
	}
	for(int i=1; i<=n; i++){
		scanf("%lf", &q[i]);
		q[i] = q[i] * 0.01;
	}
	DFS1(1,0);
	DFS2(1,0,0);
	for(int i=1; i<=n; i++)
		ans = ans + (1.0-g[i]);
	printf("%.6f", ans);
	return 0;
}