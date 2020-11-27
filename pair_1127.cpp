#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, m, father[MaxN], ans;
bool tree[MaxN];
struct Edge{
	int u, v, w;
	bool operator < (const Edge &y) const{
		return w > y.w;
	}
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

inline int Find(int x){
	return father[x] == x? x : father[x] = Find(father[x]);
}

inline void Kruskal(){
	sort(edge+1, edge+1+m);
	for(int i=1; i<=m; i++){
		int x = Find(edge[i].u), y = Find(edge[i].v);
		if(x != y && (tree[x] || tree[y])){
			father[x] = y;
			ans += edge[i].w;
			tree[y] = tree[x] & tree[y];
		}
		else if(x == y && tree[x]){
			tree[x] = false;
			ans += edge[i].w;
		}
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		father[i] = i;
		tree[i] = true;
	}
	for(int i=1; i<=m; i++)
		edge[i].u = Read(), edge[i].v = Read(), edge[i].w = Read();
	Kruskal();
	printf("%lld", ans);
	return 0;
}