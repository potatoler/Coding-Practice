#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, MaxM = 500005;
int n, m, cntEdge, head[MaxN];
int cntDFN, DFN[MaxN], LOW[MaxN], sz[MaxN], ans[MaxN];
bool cut[MaxN];
struct Edge{
	int destination, nextEdge;
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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void Tarjan(int x){
	DFN[x] = LOW[x] = ++cntDFN;
	sz[x] = 1;
	int sum = 0, cntSub = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(!DFN[y]){
			Tarjan(y);
			sz[x] += sz[y];
			LOW[x] = min(LOW[x], LOW[y]);
			if(LOW[y] >= DFN[x]){
				ans[x] += sz[y] * (n-sz[y]);
				sum += sz[y];
				cntSub++;
				if(x != 1 || cntSub > 1) cut[x] = true;
			}
		}
		else LOW[x] = min(LOW[x], DFN[y]);
	}
	if(!cut[x]) ans[x] = 2 * (n-1);
	else ans[x] += (n-sum-1) * (sum+1) + (n-1);
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u= Read(), v = Read();
		AddEdge(u,v), AddEdge(v,u);
	}
	Tarjan(1);
	for(int i=1; i<=n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}