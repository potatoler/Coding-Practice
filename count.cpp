#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
const int MaxN = 3003, MaxM = 12, Mod = 998244353;
using namespace std;
int n, m, C[MaxN][MaxM];

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

struct Edge{
	int destination, nextEdge;
};
class Tree{
	private:
	int head[MaxN], cntEdge;
	Edge edge[MaxN*2];
	
	public:
	int size, degree[MaxN];
	
	inline void AddEdge(int u, int v){
		cntEdge++;
		edge[cntEdge].destination = v;
		edge[cntEdge].nextEdge = head[u];
		head[u] = cntEdge;
		return;
	}
	
	inline void Plant(int x){
		size = x;
		for(int i=1; i<size; i++){
			int u = Read(), v = Read();
			AddEdge(u, v);
			AddEdge(v, u);
			degree[u]++;
			degree[v]++;
		}
		return;
	}
}T1, T2;



signed main(){
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	C[1][0] = C[1][1] = 1;
	for(int i = 2; i < MaxN; i++){
		C[i][0] = 1;
		for (int j = 1; j < MaxM; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]);
	}
	n = Read(), T1.Plant(n);
	m = Read(), T2.Plant(m);
	if(n < m){
		printf("0");
		return 0;
	}
	int ans = 0;
	for(int i=1; i<=n; i++)
		printf("%lld ", T1.degree[i]);
	printf("\n");
	for(int i=1; i<=n; i++){
		ans += C[T1.degree[i]][T2.size-1];
	}
	printf("%lld", ans);
	return 0;
}