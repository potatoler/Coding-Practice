#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 102, MaxM = 3003 * MaxN;
int n, m, a[MaxN], head[MaxM], cntEdge, dis[MaxM], ans;
bool inQueue[MaxM];
queue<int> q;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxM * 2];

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

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	sort(a+1, a+n+1);
	int x = max(1LL, a[1]-m);
	if(x == 1){
		printf("-1");
		return 0;
	}
	for(int i=1; i<=n; i++){
		for(int j=max(a[i-1]+1, a[i]-m); j<=a[i]; j++){
			if(j != x){
				for(int k=0; k<x; k++)
					AddEdge(k, (k+j)%x, j);
			}
		}
	}
	for(int i=0; i<MaxM; i++)
		dis[i] = LLONG_MAX;
	dis[0] = 0;
	q.push(0);
	while(q.size()){
		int u = q.front();
		q.pop();
		inQueue[u] = false;
		for(int i = head[u]; i; i = edge[i].nextEdge){
			int v = edge[i].destination, w = edge[i].value;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				if(!inQueue[v]) inQueue[v] = true, q.push(v);
			}
		}
	}
	dis[x] = 0;
	for(int i=1; i<x; i++){
		if(dis[i] > LLONG_MAX){
			printf("-1");
			return 0;
		}
		ans = max(ans, dis[i]-x);
	}
	printf("%lld", ans);
	return 0;
}