#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int h, x, y, z, dis[MaxN], ans, head[MaxN], cntEdge;
bool inQueue[MaxN];
queue<int> Q;
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN * 2];

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
	edge[cntEdge].value = w;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void SPFA(){
	memset(dis, 0x3f, sizeof(dis));
	dis[1%x] = 1;
	Q.push(1%x);
	inQueue[1%x] = true;
	while(Q.size()){
		int x = Q.front();
		Q.pop();
		inQueue[x] = false;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(dis[y] > dis[x] + edge[i].value){
				dis[y] = dis[x] + edge[i].value;
				if(!inQueue[y]){
					Q.push(y);
					inQueue[y] = true;
				}
			}
		}
	}
}

signed main(){
	h = Read(), x = Read(), y = Read(), z = Read();
	for(int i=0; i<x; i++)
		AddEdge(i, (i+y)%x, y), AddEdge(i, (i+z)%x, z);
	SPFA();
	for(int i=0; i<x; i++)
		if(dis[i] <= h) ans += (h-dis[i]) / x + 1;
	printf("%lld", ans);
	return 0;
}