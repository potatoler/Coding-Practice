#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, cntEdge, head[MaxN], cntVertex, sumCow;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN * 2];
struct Vertex{
	int depth, father, answer, cow, subtreeCow;
}vertex[MaxN];
#define thisSon edge[i].destination

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

inline int DFS1(int x){
	int tot = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].father = x;
		int sum = DFS1(thisSon);
		vertex[x].depth += vertex[thisSon].depth + edge[i].value * sum;
		tot += sum;
	}
	return vertex[x].subtreeCow = tot + vertex[x].cow;
}

inline void DFS2(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].answer = vertex[x].answer - vertex[thisSon].subtreeCow * edge[i].value + (sumCow - vertex[thisSon].subtreeCow) * edge[i].value;
		DFS2(thisSon);
	}
}

signed main(){
	n = Read();
	for(int i=1;i<=n;i++)
		vertex[i].cow = Read();
	for(int i=1;i<=n;i++)
		sumCow += vertex[i].cow;
	for(int i=1;i<n;i++){
			int u = Read(), v = Read(), w = Read();
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
	DFS1(1);
	DFS2(1);
//	for(int i=1;i<=n;i++)
//		printf("%lld ",vertex[i].answer);
//	printf("\n");
	int ans = INT_MAX;
		for(int i=1;i<=n;i++)
			if(vertex[i].answer < ans) ans = vertex[i].answer;
		printf("%lld",ans + vertex[1].depth);
}