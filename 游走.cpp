#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 505;
int n, m, du[MaxN];
double num[MaxN][MaxN], ans, expectation[MaxN*MaxN];
int from[MaxN*MaxN], to[MaxN*MaxN], head[MaxN], tot;
struct Edge{
	int nextEdge,destination;
}edge[MaxN*MaxN*2];

void AddEdge(int u,int v){
	tot++;
	edge[tot].destination = v;
	edge[tot].nextEdge = head[u];
	head[u] = tot;
	du[u]++;
}

void Gauss(int p){
	num[1][n] = 1;
	for(int i = 1;i < n;i++){
		num[i][i] = 1;
		for(int j = head[i];j;j = edge[j].nextEdge){
			int v = edge[j].destination;
			if(v != n) num[i][v] = -1.0 / du[v];
		}
	}
	for(int i = 1;i < p;i++){
		if(fabs(num[i][i]) < 1e-8){
			int r = i + 1;
			while(r <= p){
				if(num[r][i]) break;
				r++;
			}
			for(int j = 1;j <= p;j++)
				swap(num[i][j],num[r][j]);
		}
		for(int j = p;j >= i;j--)
			num[i][j] /= num[i][i];
		for(int j = 1;j < p;j++){
			if(i != j){
				for(int k = p;k >= i;k--)
					num[j][k] -= num[j][i] * num[i][k];
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		from[i] = u;
		to[i] = v;
		AddEdge(u,v), AddEdge(v,u);
	}
	Gauss(n);
	for(int i = 1;i <= m;i++){
		if(from[i] != n) expectation[i] += num[from[i]][n] * 1.0 / du[from[i]];
		if(to[i] != n) expectation[i] += num[to[i]][n] * 1.0 / du[to[i]];
	}
	sort(expectation+1, expectation+m+1);
	for(int i = 1;i <= m;i++)
		ans += expectation[i] * 1.0 * (m - i + 1);
	printf("%.3lf\n", ans);
	return 0;
}