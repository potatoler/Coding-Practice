#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int short
using namespace std;
const int MaxN = 500;
int n, c, father[MaxN], depth[MaxN], head[MaxN], cntEdge, ans = 0x3f3f;
int stack[MaxN], top;
struct Vertex{
	int father, depth, subtreeSize, chainTop, heavySon;
	bool berry;
}vertex[MaxN];
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination
int f[MaxN][MaxN][2][MaxN];

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

int min(int a, int b){return a < b ? a : b;}
int max(int a, int b){return a > b ? a : b;}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline bool DFS1(int x, int fa){
//	printf("%lld %lld\n", x, vertex[x].berry);
	vertex[x].subtreeSize = 1;
	vertex[x].father = fa;
	vertex[x].depth = vertex[fa].depth+1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father) continue;
		vertex[x].berry &= 1 ^ DFS1(thisSon, x);
//		printf("%lld ", vertex[x].berry);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
//	printf("%lld %lld\n", x, vertex[x].berry);
	if(vertex[x].berry) stack[++top] = x;
	return vertex[x].berry;
}

inline void DFS2(int x, int thisTop){
	vertex[x].chainTop = thisTop;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, thisTop);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
	return;
}

inline int LCA(int x, int y){
	while(xTop != yTop){
		if(vertex[xTop].depth < vertex[yTop].depth) swap(x,y);
		x = vertex[xTop].father;
	}
	if(vertex[x].depth > vertex[y].depth) swap(x,y);
	return x;
}

inline int Value(int x, int y){
	x = stack[x], y = stack[y];
	if(!x) return (short)vertex[y].depth - 1;
	return vertex[y].depth - vertex[LCA(x,y)].depth;
}

inline int &F(int i, int j, int k, int l){
	if(j == i-1) return f[i][k][0][l];
	return f[i][j][1][l];
}

signed main(){
	n = Read(), c = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u,v);
		AddEdge(v,u);
	}
	for(int i=1; i<=c; i++){
		int x = Read();
		vertex[x].berry = 1;
	}
	DFS1(1,0);
	DFS2(1,1);
	for(int i=0;i<=top+1;i++)
		for(int j=0;j<=top;j++)
			for(int l=0;l<=n;l++)
				f[i][j][0][l] = f[i][j][1][l] = 0x3f3f;
	f[1][0][0][0] = f[1][0][1][0] = 0;
	for(int i=1; i<=top; i++){
		for(int j=0; j<i; j++){
			for(int k=(j==i-1? 0 : i-1); k<=i-1; k++){
				for(int l=0; l<n; l++){
					F(i+1, i, k, l+Value(j,i)) = min(F(i+1, i, k, l+Value(j,i)), F(i,j,k,l));
					F(i+1, j, i, l) = min(F(i+1,j,i,l), F(i,j,k,l) + Value(k,i));
				}
			}
		}
	}
	for(int i=0; i<=top; i++){
		for(int j=0; j<n; j++)
			ans = min(ans, max(min(F(top+1, i, top, j), F(top+1, top, i, j)), j));
	}
	cout<<ans*2;
	return 0;
}