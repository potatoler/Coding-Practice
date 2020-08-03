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
const int MaxN = 100005;
int n, m, head[MaxN], cntEdge;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN];
struct Vertex{
	int DFN, LOW, unit;
	bool visited;
}vertex[MaxN];
int cntDFN, top, stack[MaxN], cntUnit, minValue[MaxN];

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

inline void Tarjan(int cur){
	vertex[cur].DFN = vertex[cur].LOW = ++cntDFN;
	stack[++top] = cur;
	vertex[cur].visited = true;

	for(int i = head[cur]; i; i = edge[i].nextEdge){
		int des = edge[i].destination;
		if(!vertex[des].DFN){
			Tarjan(des);
			vertex[cur].LOW = min(vertex[cur].LOW, vertex[des].LOW);
		}
		else if(vertex[des].visited) vertex[cur].LOW = min(vertex[cur].LOW, vertex[des].DFN);
	}
	if(vertex[cur].DFN == vertex[cur].LOW){
		++cntUnit;
		int v;
		do{
			v = stack[top--];
			vertex[v].visited = false;
			vertex[v].unit = cntUnit;
		}while(cur!=v);
	}
	return;
}

inline void Construct(){
	for(int i=1;i<=n;i++)
		for(int j = head[i]; j; j = edge[j].nextEdge){
			int des = edge[j].destination;
			if(vertex[i].unit != vertex[des].unit) minValue[vertex[des].unit] = min(minValue[vertex[des].unit], edge[j].value);
		}
	return;
}

inline void Reset(){// Haruki, Reset!
	for(int i=1;i<MaxN;i++)
		head[i] = vertex[i].DFN = vertex[i].LOW = vertex[i].unit = stack[i] = vertex[i].visited = 0;
	for(int i=1;i<MaxN;i++)
		minValue[i] = INT_MAX;
	cntEdge = cntDFN = cntUnit = top = 0;
	return;
}

signed main(){
	// freopen("message.in", "r", stdin);
	// freopen("message.out", "w", stdout);
	while(scanf("%lld%lld", &n, &m) != EOF){
		if(n == 0 && m == 0) break;
		Reset();
		for(int i=1;i<=m;i++){
			int u = Read(), v = Read(), w = Read();
			AddEdge(u+1, v+1, w);
		}
		for(int i=1;i<=n;i++)
			if(!vertex[i].DFN) Tarjan(i);
		Construct();
		int ans = 0;
		for(int i=1;i<=cntUnit;i++){
			if(minValue[i] == INT_MAX) continue;
			ans += minValue[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}