#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define int long long
using namespace std;
const int MaxN = 200005, MaxM = MaxN*2;
int n, m, q, ans, head[MaxN], cntEdge=1, path[MaxM*10][2], cntDFN, cntSCC, sccSize[MaxN], stack[MaxN], top;
bool visited[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxM*10];
int DFN[MaxN], LOW[MaxN], belong[MaxN], father[MaxN][20], depth[MaxN], value[MaxN][20], valueSqr[MaxN][20];

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
	if(u == v) return;
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void Tarjan(int x, int fa){
	LOW[x] = DFN[x] = ++cntDFN;
	stack[++top] = x;
	visited[x] = true;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(i == (fa^1)) continue;
//		if(y == fa) continue;
		if(!DFN[y]){
			Tarjan(y, i);
			LOW[x] = min(LOW[x], LOW[y]);
		}
		else if(visited[y]) LOW[x] = min(LOW[x], DFN[y]);
	}
	if(LOW[x] == DFN[x]){
		cntSCC++;
		int y = 0;
		while(x != y){
			y = stack[top--];
			belong[y] = cntSCC;
			sccSize[cntSCC]++;
			visited[y] = false;
		}
	}
	return;
}

inline void DFS(int x){
	visited[x] = true;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(visited[y]) continue;
		depth[y] = depth[x]+1;
		father[y][0] = x;
		value[y][0] = sccSize[y];
		valueSqr[y][0] = sccSize[y] * sccSize[y];
		DFS(y);
	}
	return;
}

inline int Ask(int x, int y){
	int a = 0, b = 0;
	for(int i=17; i>=0; i--){
		if(depth[father[x][i]] >= depth[y]){
			a += value[x][i];
			b += valueSqr[x][i];
			x = father[x][i];
		}
	}
	for(int i=17; i>=0; i--){
		if(depth[father[y][i]] >= depth[x]){
			a += value[y][i];
			b += valueSqr[y][i];
			y = father[y][i];
		}
	}
	for(int i=17; i>=0; i--){
		if(father[x][i] != father[y][i]){
			a += value[x][i];
			b += valueSqr[x][i];
			x = father[x][i];
			a += value[y][i];
			b += valueSqr[y][i];
			y = father[y][i];
		}
	}
	if(x != y){
		a += value[x][0] + value[y][0];
		b += valueSqr[x][0] + valueSqr[y][0];
		x = father[x][0];
	}
	a += value[x][0];
	b += valueSqr[x][0];
	return a*a - b;
}

signed main(){
	n = Read(), m = Read(), q = Read();
	for(int i=1; i<=n; i++)
		belong[i] = i;
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
		path[i][0] = u, path[i][1] = v;
	}
	Tarjan(1, 0);
	cntEdge = 1;
	memset(head, 0, sizeof(head));
	memset(visited, false, sizeof(visited));
	for(int i=1; i<=m; i++){
		int u = belong[path[i][0]], v = belong[path[i][1]];
		AddEdge(u, v), AddEdge(v, u);
	}
	depth[1] = 1;
	value[1][0] = sccSize[1];
	valueSqr[1][0] = sccSize[1] * sccSize[1];
	DFS(1);
	for(int j=1; j<=17; j++){
		for(int i=1; i<=n; i++){
			father[i][j] = father[father[i][j-1]][j-1];
			if(father[i][j]){
				value[i][j] = value[i][j-1] + value[father[i][j-1]][j-1];
				valueSqr[i][j] = valueSqr[i][j-1] + valueSqr[father[i][j-1]][j-1];
			}
		}
	}
	while(q--){
		int x = Read(), y = Read();
		ans += Ask(belong[x], belong[y]);
	}
	printf("%lld", ans);
	return 0;
}