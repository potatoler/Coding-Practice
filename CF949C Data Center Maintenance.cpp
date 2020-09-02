#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, h, head[MaxN], cntEgde, cntDFN, DFN[MaxN], LOW[MaxN], cntSCC, SCC[MaxN], SCC_Size[MaxN], degree[MaxN], a[MaxN];
int stack[MaxN], top, ans;
bool visited[MaxN], inStack[MaxN];
struct Edge{
	int from, destination, nextEdge;
}edge[MaxN * 2];
#define des edge[i].destination

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
	cntEgde++;
	edge[cntEgde].from = u;
	edge[cntEgde].destination = v;
	edge[cntEgde].nextEdge = head[u];
	head[u] = cntEgde;
	return;
}

inline void Tarjan(int x){
	LOW[x] = DFN[x] = ++cntDFN;
	visited[x] = true;
	stack[++top] = x;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(!DFN[des]){
			Tarjan(des);
			LOW[x] = min(LOW[x], LOW[des]);
		}
		else if(visited[des]) LOW[x] = min(LOW[x], DFN[des]);
	}
	if(LOW[x] == DFN[x]){
		int tmp;
		cntSCC++;
		do{
			tmp = stack[top--];
			SCC[tmp] = cntSCC;
			visited[tmp]= false;
			SCC_Size[cntSCC]++;
		}while(tmp != x);
	}
}

signed main(){
	n = Read(), m = Read(), h = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		if((a[u]+1) % h == a[v]) AddEdge(u,v);
		if((a[v]+1) % h == a[u]) AddEdge(v,u);
	}
	for(int i=1; i<=n; i++)
		if(!DFN[i]) Tarjan(i);
	for(int i=1; i<=cntEgde; i++){
		int u = SCC[edge[i].from], v = SCC[edge[i].destination];
		if(u^v) degree[u]++;
	}
	// for(int i=1; i<=n; i++)
	// 	printf("%lld%lld ", DFN[i], SCC[i]);
	// printf("\n");
	SCC_Size[0] = INT_MAX;
	for(int i=1; i<=cntSCC; i++)
		if(!degree[i]) if(SCC_Size[i] < SCC_Size[ans]) ans = i;
	printf("%lld\n", SCC_Size[ans]);
	for(int i=1; i<=n; i++)
		if(SCC[i] == ans) printf("%lld ", i);
	return 0;
}