#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1003, MaxM = 100005;
int n, m, head[MaxN], cntEdge, belong[MaxN], cntUnit, len[MaxN];
bool cannot;
struct Edge{
	int destination, nextEdge;
}edge[MaxM * 2];

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

inline void DFS(int x, int un){
	if(cannot) return;
	belong[x] = un;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(cannot) return;
		if(belong[y] == un){
			cannot = true;
			return;
		}
		if(belong[y] == -un) continue;
		DFS(y, -un);
	}
	return;
}

inline int BFS(int x){
	bool visited[MaxN] = {false};
	int queue[MaxN][2] = {0};
	int hd = 0, tl = 1, length = 0;
	queue[1][0] = x; 
	visited[x] = true;
	while(hd < tl){
		hd++;
		int cur = queue[hd][0];
		length = max(length, queue[hd][1]);
		for (int i = head[cur]; i; i = edge[i].nextEdge){
			int des = edge[i].destination;
			if(!visited[des]){
				visited[des]=1;
				tl++;
				queue[tl][0] = des;
				queue[tl][1] = queue[hd][1] + 1;
			}
		}
	}
//	for(int i=1; i<=tail; i++)
//		printf("%lld ", queue[i][1]);
//	printf("\n");
//	for(int i=1; i<=tail; i++)
//		printf("%lld ", queue[i][2]);	
	return length;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		AddEdge(u,v), AddEdge(v, u);
	}
	for(int i=1; i<=n; i++){
		if(!belong[i]) DFS(i, ++cntUnit);
		if(cannot){
			printf("-1");
			return 0;
		}
	}
//	for(int i=1; i<=n; i++)
//		printf("%lld ", belong[i]);
	for(int i=1; i<=n; i++)
		len[abs(belong[i])] = max(len[abs(belong[i])], BFS(i));
	for(int i=1; i<=cntUnit; i++)
		len[0] += len[i];
	printf("%lld", len[0]);
	return 0;
}