#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1000005;
int n, cntEdge, head[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];
struct Vertex{
	int depth, father, subtreeSize, answer;
}vertex[MaxN];
#define thisSon edge[i].destination

inline int Read(){
	char x; int num;
	while(x = getchar(), x < '0' || x > '9');
	num = x - '0';
	while(x = getchar(), x >= '0' && x <= '9'){
		num *= 10;
		num += x - '0';
	}
	return num;
}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].father = x;
		vertex[thisSon].depth = vertex[x].depth + 1;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
	}
}

inline void DFS2(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[thisSon].answer = vertex[x].answer - 2*vertex[thisSon].subtreeSize + vertex[1].subtreeSize;
		DFS2(thisSon);
	}
}

signed main(){
	n = Read();
	for(int i=1;i<n;i++){
		int u = Read(), v = Read();
		AddEdge(u, v);
		AddEdge(v, u);
	}
	DFS1(1);
	for(int i=1;i<=n;i++)
		vertex[1].answer += vertex[i].depth;
	DFS2(1);
	int ans = -INT_MAX, ID = 0;
	for(int i=1;i<=n;i++)
		if(vertex[i].answer > ans){
			ans = vertex[i].answer;
			ID = i;
		}
	printf("%lld", ID);
	return 0;
}