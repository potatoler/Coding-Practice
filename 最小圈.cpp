#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int MaxN = 3005, MaxM = 10005;
int cntEdge, n, m, head[MaxN];
struct Edge{
	int destination, nextEdge;
	double value;
}edge[MaxM*2];
double dis[MaxM];
bool vis[MaxN];
#define des edge[i].destination

inline void AddEdge(int u, int v, double w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
}

bool SPFA_Judge(int x, double mid){
	vis[x] = true;
	for(int i=head[x]; i; i=edge[i].nextEdge){
		if(dis[des] > dis[x]+edge[i].value-mid){
			dis[des] = dis[x] + edge[i].value - mid;
			if(vis[des] || SPFA_Judge(des, mid)) return 1;
		}
	}
	vis[x] = 0;
	return 0;
}

double Check(double mid){
	for(int i=1;i<=n;i++)
		dis[i] = 0;
	memset(vis, false, sizeof(vis));
	for(int i=1;i<=n;i++) if(SPFA_Judge(i, mid)) return 1;
	return 0;		
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u, v;
		double w;
		scanf("%d%d%lf",&u,&v,&w);
		AddEdge(u, v, w);
	}
	double l = -1e7, r = 1e7;
	while(r-l > 1e-11){
		double mid = (l+r) / 2.0;
		if(Check(mid)) r = mid;
		else l = mid;
	}
	printf("%.8lf\n", r);
	return 0;
}