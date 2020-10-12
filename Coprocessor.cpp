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
const int MaxN = 100005;
int n, m, cntEdge, head[MaxN], degree[MaxN], ans;
bool co[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN];
queue<int> cmp, cop;

inline void Topo(){
	for(int i=1; i<=n; i++)
		if(!degree[i]) co[i]? cop.push(i) : cmp.push(i);
	while(cop.size() || cmp.size()){
		while(cmp.size()){
			int x = cmp.front();
			cmp.pop();
			for(int i = head[x]; i; i = edge[i].nextEdge){
				int y = edge[i].destination;
				degree[y]--;
				if(!degree[y]) co[y]? cop.push(y) : cmp.push(y);
			}
		}
		if(cop.size()) ans++;
		while(cop.size()){
			int x = cop.front();
			cop.pop();
			for(int i = head[x]; i; i = edge[i].nextEdge){
				int y = edge[i].destination;
				degree[y]--;
				if(!degree[y]) co[y]? cop.push(y) : cmp.push(y);
			}
		}
	}
}

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

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		co[i] = Read();
	for(int i=1; i<=m; i++){
		int v = Read()+1, u = Read()+1;
		AddEdge(u, v);
		degree[v]++;
	}
	Topo();
	printf("%lld\n", ans);
	return 0;
}