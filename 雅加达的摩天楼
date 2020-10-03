#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int MaxN = 30004, MaxM = 18000007;
int n, m, s, t, blockSize;
int head[MaxN*102], id[102][MaxN], dis[MaxN*102], cntEdge;
bool visited[MaxN*102];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxM];
queue<int> q;

inline int Read(){
	int num = 0, op = 1;
	char ch= getchar();
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
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline int SPFA(int s, int t){
	for(int i=0; i<MaxN*102; i++)
		dis[i] = INT_MAX;
	dis[s] = 0;
	q.push(s);
	while(q.size()){
		int x = q.front();
		q.pop();
		visited[x] = false;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(dis[y] > dis[x] + edge[i].value){
				dis[y] = dis[x] + edge[i].value;
				if(!visited[y]){
					q.push(y);
					visited[y] = true;
				}
			}
		}
	}
	return dis[t] != INT_MAX ? dis[t] : -1;
}

signed main(){
	n = Read(), m = Read();
	blockSize = sqrt(n/3);
	for(int i=1; i<=blockSize; i++)
		for(int j=0; j<n; j++)
			id[i][j] = i * n + j;
	for(int i=1; i<=blockSize; i++){
		for(int j=0; j<n; j++){
			AddEdge(id[i][j], j, 0);
			if(i + j >= n) break;
			AddEdge(id[i][j], id[i][j+i], 1);
			AddEdge(id[i][j+i], id[i][j], 1);
		}
	}
	for(int i=0; i<m; i++){
		int b = Read(), p = Read();
		if(p <= blockSize) AddEdge(b, id[p][b], 0);
		else{
			for(int j=1; b+j*p < n; j++)
				AddEdge(b, b+j*p, j);
			for(int j=1; b-j*p >= 0; j++)
				AddEdge(b, b-j*p, j);
		}
		if(i == 0) s = b;
		if(i == 1) t = b;
	}
	for(int i=1; i<=blockSize; i++)
		for(int j=0; j<n; j++)
			if(head[id[i][j]]) AddEdge(id[i][j], j, 0);
	int ans = SPFA(s, t);
	printf("%d", ans);
	return 0;
}