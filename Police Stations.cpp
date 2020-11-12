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
const int MaxN = 300005;
int n, k, d, head[MaxN], cntEdge, cntColour, c[MaxN], ans[MaxN], cntAnswer;
int fr[MaxN], to[MaxN];
struct Edge{
	int destiantion, nextEdge;
}edge[MaxN*2];
struct City{
	int serial, colour;
};
queue<City> q;

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
	edge[cntEdge].destiantion = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void BFS(){
	while(q.size()){
		City x = q.front();
		q.pop();
		for(int i = head[x.serial]; i; i = edge[i].nextEdge){
			int y = edge[i].destiantion;
			if(!c[y]){
				c[y] = x.colour;
				q.push((City){y,x.colour});
			}
		}
	}
	return;
}

signed main(){
	n = Read(), k = Read(), d = Read();
	for(int i=1; i<=k; i++){
		int x = Read();
		if(!c[x]){
			c[x] = ++cntColour;
			q.push((City){x, cntColour});
		}
	}
//	for(int i=1; i<=n; i++)
//		printf("%lld ", c[i]);
//	printf("\n");
	for(int i=1; i<n; i++){
		fr[i] = Read(), to[i] = Read();
		AddEdge(fr[i],to[i]), AddEdge(to[i],fr[i]);
	}
	BFS();
	for(int i=1; i<n; i++){
//		printf("%lld %lld\n", edge[i].fr, edge[i].to);
		if(c[fr[i]] != c[to[i]]) ans[++cntAnswer] = i;
	}
	printf("%lld\n", cntAnswer);
	for(int i=1; i<=cntAnswer; i++)
		printf("%lld ", ans[i]);
	return 0;
}