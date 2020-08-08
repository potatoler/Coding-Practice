#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1003;
int N, M, C,  m[MaxN], head[MaxN], f[MaxN][MaxN], cntEdge, ans = 0;
struct Edge{
	int destination, nextEdge;
}edge[MaxN * 2];

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-')  op = -1;
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
//	freopen("time.in", "r", stdin);
//	freopen("time.out", "w", stdout);
	N = Read(), M = Read(), C = Read();
	for(int i=1; i<=N ;i++)
		m[i] = Read();
	for(int i=1; i<=M; i++){
		int u = Read(), v = Read();
		AddEdge(v, u);
	}
	memset(f, -1, sizeof(f));
	f[0][1] = 0;
	for(int i=1; i<=1000; i++){
		for(int j=1; j<=N; j++){
			for(int k = head[j]; k; k = edge[k].nextEdge){
				int des = edge[k].destination;
				if(~f[i-1][des]) f[i][j] = max(f[i][j], f[i-1][des] + m[j]);
				
			}
		}
		ans = max(ans, f[i][1] - C*i*i);
	}
	printf("%lld", ans);
	return 0;
}