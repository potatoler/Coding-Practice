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
const int MaxN = 80004, MaxM = 200005;
int n, m, s, ans, cntEdge, cntNewEdge, head[MaxN], newHead[MaxN], cntDFN, DFN[MaxN], LOW[MaxN], stack[MaxN], top, belong[MaxN], cntSCC, dis[MaxN], value[MaxN];
bool visited[MaxN];
struct Edge{
	int from, to, nextEdge, value;
	double cure;
}edge[MaxM];
struct NewEdge{
	int destination, nextEdge, value;
}newEdge[MaxM];

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

inline void AddEdge(int u, int v, int w, double c){
	cntEdge++;
	edge[cntEdge].from = u;
	edge[cntEdge].to = v;
	edge[cntEdge].value = w;
	edge[cntEdge].cure = c;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void AddNewEdge(int u, int v, int w){
	cntNewEdge++;
	newEdge[cntNewEdge].destination = v;
	newEdge[cntNewEdge].nextEdge = newHead[u];
	newEdge[cntNewEdge].value = w;
	newHead[u] = cntNewEdge;
	return;
}

inline void Tarjan(int x){
	DFN[x] = LOW[x] = ++cntDFN;
	visited[x] = true;
	stack[++top] = x;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].to;
		if(!DFN[y]){
			Tarjan(y);
			LOW[x] = min(LOW[x], LOW[y]);
		}
		else if(visited[y]) LOW[x] = min(LOW[x], DFN[y]);
	}
	if(DFN[x] == LOW[x]){
		cntSCC++;
		belong[x] = cntSCC;
		visited[x] = false;
		while(stack[top] != x){
			belong[stack[top]] = cntSCC;
			visited[stack[top--]] = false;
		}
		top--;
	}
}


inline void SPFA(){
	memset(visited, false, sizeof(visited));
//	memset(dis, -1, sizeof(dis));
	queue<int> q;
	q.push(s);
	dis[s] = value[s];
	visited[s] = true;
	while(q.size()){
		int x = q.front();
		q.pop();
		visited[x] = false;
		for(int i = newHead[x]; i; i = newEdge[i].nextEdge){
			int y = newEdge[i].destination, z = newEdge[i].value;
			if(dis[y] < dis[x] + z + value[y]){
				dis[y] = dis[x] + z + value[y];
				if(!visited[y]){
					visited[y] = true;
					q.push(y);
				}
			}
		}
	}
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		double c;
		scanf("%lf", &c);
		AddEdge(u, v, w, c);
//		printf("%lld %lld\n", edge[cntEdge].from, edge[cntEdge].to);
	}
	for(int i=1; i<=n; i++)
		if(!DFN[i]) Tarjan(i);
//	for(int i=1; i<=n; i++)
//		printf("%lld ", belong[i]);
	for(int i=1; i<=m; i++){
		int from = edge[i].from, to = edge[i].to;
		if(belong[from] == belong[to]){
			int serial = belong[from], val = edge[i].value;
			while(val){
				value[serial] += val;
				val = (int) val * edge[i].cure;
			}
		}
		else AddNewEdge(belong[from], belong[to], edge[i].value);
//		printf("%lld\n", newEdge[cntNewEdge].destination);
	}
	s = belong[Read()];
	SPFA();
	for(int i=1; i<=cntSCC; i++)
		ans = max(dis[i], ans);
	printf("%lld", ans);
	return 0;
}