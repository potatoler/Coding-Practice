#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 1000006, MaxM = 100005;
int n, m, head[MaxN], cntEdge, cntDFN, ans;
int col[MaxN], serial[MaxN], st[MaxM], ed[MaxM], tag[MaxN], suball[MaxN], father[MaxN][20], DFN[MaxN], depth[MaxN];
int ver[MaxN][2], dis[MaxN][2];// longest path vertex and longest path length, both for subtree and non-subtree part
struct Edge{
	int destination, nextEdge;
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

inline bool cmp(int x, int y){
	return DFN[x] < DFN[y];
}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS1(int x, int f){
	father[x][0] = f;
	for(int i=1; i<20; i++)
		father[x][i] = father[father[x][i-1]][i-1];
	depth[x] = depth[f] + 1;
	DFN[x] = ++cntDFN;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == f) continue;
		DFS1(y,x);
		if(dis[y][0] + 1 >= dis[x][0]){
			ver[x][1] = ver[x][0];
			dis[x][1] = dis[x][0];
			ver[x][0] = y;
			dis[x][0] = dis[y][0] + 1;
		}
		else if(dis[y][0] + 1 >= dis[x][1]){
			ver[x][1] = y;
			dis[x][1] = dis[y][0] + 1;
		}
	}
	return;
}

inline void DFS2(int x, int f, int res){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == f) continue;
		if(ver[x][0] == y) DFS2(y, x, max(res, dis[x][1]) + 1);
		else DFS2(y, x, max(res, dis[x][0]) + 1);
		tag[x] += tag[y];
		suball[x] += suball[y];
	}
	if(tag[x] == m) ans = max(ans, res+1);
	if(suball[x] == 0) ans = max(ans, dis[x][0]+2);
}

inline int LCA(int x, int y){
	if(depth[x] < depth[y]) swap(x,y);
	for(int i=19; i>=0; i--)
		if(depth[x] - (1<<i) >= depth[y]) x = father[x][i];
	if(x == y) return x;
	for(int i=19; i>=0; i--){
		if(father[x][i] != father[y][i]){
			x = father[x][i];
			y = father[y][i];
		}
	}
	return father[x][0];
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		col[i] = Read();
		serial[i] = i;
	}
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v);
		AddEdge(v,u);
	}
	DFS1(1,0);
//	exit(0);
	sort(serial+1, serial+1+n, cmp);
	for(int i=1; i<=n; i++){
		if(ed[col[serial[i]]]){
			tag[serial[i]]++;
			tag[LCA(serial[i],ed[col[serial[i]]])]--;
		}
		else{
			tag[serial[i]]++;
			st[col[serial[i]]] = serial[i];
		}
		ed[col[serial[i]]] = serial[i];
	}
	for(int i=1; i<=m; i++)
		suball[LCA(st[i], ed[i])]++;
//	exit(0);
	DFS2(1, 0, 0);
	printf("%lld\n", ans);
	return 0;
}