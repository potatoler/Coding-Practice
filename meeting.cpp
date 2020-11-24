#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 102;
typedef pair<int,int> int_pair;
int n, m, b, e, p;
int head[MaxN], cntEdge;
bool dis[MaxN][MaxN*MaxN], exist[MaxN*MaxN];
struct Edge{
	int destination, nextEdge, value[2];
}edge[MaxN*MaxN];

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

inline void AddEdge(int u, int v, int w0, int w1){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value[0] = w0;
	edge[cntEdge].value[1] = w1;
	head[u] = cntEdge;
	return;
}

inline void BFS(int type){
	memset(dis, false, sizeof(dis));
	queue<int_pair> q;
	q.push(make_pair(0,1));
	dis[1][0] = true;
	while(q.size()){
		int d = q.front().first, x = q.front().second;
		q.pop();
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination, z = edge[i].value[type];
			if(!dis[y][d+z]){
				dis[y][d+z] = true;
				q.push(make_pair(d+z, y));
			}
		}
	}
	if(type == 0){
		for(int i=0; i<=10000; i++)
			if(dis[n][i]) exist[i] = true;
	}
	else{
		for(int i=0; i<=10000; i++){
			if(dis[n][i] && exist[i]){
				printf("%lld", i);
				return;
			}
		}
		printf("IMPOSSIBLE");
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w0 = Read(), w1 = Read();
		AddEdge(u, v, w0, w1);
	}
	BFS(0);
	BFS(1);
	return 0;
}