#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100000, MaxM = 500000;
struct Edge{
	int destination, nextEdge;
}edge[MaxM];
int n, m, cntEdge, cntDFN, DFN[MaxN], LOW[MaxN], head[MaxN], cntBridge[MaxN];
bool vis[MaxN];
#define des edge[i].destination

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
}

inline void Tarjan(int x, int fa){
	cntDFN++;
	DFN[x] = cntDFN;
	LOW[x] = cntDFN;
	vis[x] = true;
	for(int i = head[x]; i; i=edge[i].nextEdge){
		if(!vis[des]){
			Tarjan(des, x);
			LOW[x] = min(LOW[x], LOW[des]);
		}
		else if(des != fa && DFN[x] > DFN[des])
			LOW[x] = min(LOW[x], DFN[des]);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		AddEdge(u, v), AddEdge(v, u);
	}
	Tarjan(1, 0);
	for(int i=1;i<=n;i++){
		for(int j=head[i]; j; j=edge[j].nextEdge){
			if(LOW[i] != LOW[edge[j].destination]){
				cntBridge[LOW[i]]++;
				cntBridge[LOW[edge[j].destination]]++;
			}
		}
	}
	int ans = 0;
	for(int i=1;i<=n;i++)
		if(cntBridge[i]/2 == 1) ans++;
	ans = (ans+1) / 2;
	printf("%d\n",ans);
	return 0;
}