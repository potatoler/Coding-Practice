#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, m[MaxN], cntEdge, head[MaxN], cntDFN, DFN[MaxN];
int stack[MaxN], top;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];
priority_queue<int> q[MaxN];

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

inline void AddEgde(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS(int u){
	DFN[u] = ++cntDFN;
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		top = 0;
		DFS(v);
		if(q[DFN[u]].size() < q[DFN[v]].size()) swap(DFN[u], DFN[v]);
		while(!q[DFN[v]].empty()){
			stack[++top] = max(q[DFN[u]].top(), q[DFN[v]].top());
			q[DFN[u]].pop(), q[DFN[v]].pop();
		}
		while(top > 0)
			q[DFN[u]].push(stack[top--]);
	}
	q[DFN[u]].push(m[u]);
	return;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		m[i] = Read();
	for(int i=2; i<=n; i++){
		int x = Read();
		AddEgde(x, i);
	}
	DFS(1);
	int ans = 0;
	while(!q[DFN[1]].empty()){
		ans += q[DFN[1]].top();
		q[DFN[1]].pop();
	}
	printf("%lld", ans);
	return 0;
}