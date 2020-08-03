#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 400010;
int n, m;
int top, stack[MaxN], DFN[MaxN], LOW[MaxN], value[MaxN], size[MaxN], step, cntSquare, ans, allSize;

struct Graph{
	int head[MaxN], to[MaxN], nextEdge[MaxN], cntEdge;
	inline void AddEdge(int u, int v){
		cntEdge++;
		to[cntEdge] = v;
		nextEdge[cntEdge] = head[u];
		head[u] = cntEdge;
		cntEdge++;
		to[cntEdge] = u;
		nextEdge[cntEdge] = head[v];
		head[v] = cntEdge;
	}
}graph, tree;

inline void TarjanBuildTree(int cur){
	LOW[cur] = DFN[cur] = ++step;
	stack[++top] = cur;
	for(int i = graph.head[cur], des; i; i = graph.nextEdge[i]){
		des = graph.to[i];
		if(!DFN[des]){
			TarjanBuildTree(des);
			LOW[cur] = min(LOW[cur], LOW[des]);
			if(LOW[des] >= DFN[cur]){
				int t = 0, cnt = 1;
				cntSquare++;
				do{
					t = stack[top--];
					cnt++;
					tree.AddEdge(t, cntSquare);
					size[cntSquare] += size[t];
				}while(t != des);
				value[cntSquare] = cnt;
				size[cur] += size[cntSquare];
				tree.AddEdge(cntSquare, cur);
			}
		}
		else LOW[cur] = min(LOW[cur], DFN[des]);
	}
}

inline void DFS(int x, int fa){
	int fl = (x <= n);
	ans += 2 * size[x] * (allSize - size[x]) * value[x];
	for(int i = tree.head[x], des; i; i = tree.nextEdge[i]){
		des = tree.to[i];
		if(des == fa) continue;
		ans += 2 * fl * size[des] * value[x];
		fl += size[des];
		DFS(des, x);
	}
	return;
}

signed main(){
	scanf("%lld%lld", &n, &m);
	cntSquare = n;
	for(int i=1;i<=n;i++){
		value[i] = -1;
		size[i] = 1;
	}
	for(int i=1;i<=m;i++){
		int u, v;
		scanf("%lld%lld", &u, &v);
		graph.AddEdge(u, v);
	}
	for(int i=1;i<=n;i++){
		if(!DFN[i]){
			TarjanBuildTree(i);
			allSize = size[i];
			DFS(i, -1);
		}
	}
	printf("%lld", ans);
	return 0;
}