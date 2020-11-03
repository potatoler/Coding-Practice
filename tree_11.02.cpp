#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<map>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, q, C, head[MaxN], cntEdge, c[MaxN];
int father[MaxN];
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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

signed main(){
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	n = Read(), q = Read(), C = Read();
	for(int i=1; i<=n; i++)
		c[i] = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v), AddEdge(v, u);
		
	}
	while(q--){
		int op = Read();
		if(op == 2){
			printf("%lld\n", n-1);
		}
		else{
			int x = Read(), y = Read();
			c[x] = y;
		}
	}
	return 0;
}