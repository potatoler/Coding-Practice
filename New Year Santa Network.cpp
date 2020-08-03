#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, head[MaxN], cntEdge;
int number[MaxN], length[MaxN], input[MaxN], output[MaxN];
double ans, tot;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN * 2];
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
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
}

inline void DFS(int x, int fa){
	number[x] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == fa) continue;
		DFS(thisSon, x);
		number[x] += number[thisSon];
		ans += (double)edge[i].value * number[thisSon] * (n-number[thisSon]) / tot;
	}
}

signed main(){
	n = Read();
	for(int i=1;i<n;i++){
		int u = Read(), v = Read(), w = Read();
		input[i] = u;
		output[i] = v;
		length[i] = w;
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	tot = (double)n*(n-1)/6.0;
	DFS(1,0);
	int m = Read();
	for(int i=1;i<=m;i++){
		int u = Read(), v = Read();
		int w = min(number[input[u]], number[output[u]]);
		ans -= (double)(length[u] - v) * w * (n-w) / tot;
		length[u] = v;
		printf("%.8lf\n", ans);
	}
	return 0;
}