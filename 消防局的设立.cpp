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
const int MaxN = 1005;
int n, ans, head[MaxN], cntEdge, depth[MaxN], father[MaxN], serial[MaxN], tag[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
#define thisSon edge[i].destination
queue<int> q;

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

inline bool cmp(int a, int b){
	return depth[a] > depth[b];
}

inline void DFS(int x){
	depth[x] = depth[father[x]] + 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father[x]) continue;
		DFS(thisSon);
	}
	return;
}

signed main(){
	n = Read();
	serial[1] = 1;
	for(int i=2; i<=n; i++){
		 serial[i] = i;
		int x = Read();
		father[i] = x;
		AddEdge(x, i), AddEdge(i, x);
	}
	DFS(1);
	sort(serial+1, serial+1+n, cmp);
	for(int i=1; i<=n; i++)
		q.push(serial[i]);
	while(q.size()){
		while(q.size() && (tag[q.front()]>0 || tag[father[q.front()]]-1>0 || tag[father[father[q.front()]]]-2>0))
			q.pop();
		if(q.empty()) break;
		int x = q.front();
		q.pop();
		ans++;
		if(x == 1) tag[x] = 3;
		else if(father[x] == 1){
			tag[father[x]] = 3;
			tag[x] = 2;
		}
		else{
			tag[father[father[father[father[x]]]]] = 1;
			tag[father[father[father[x]]]] = 2;
			tag[father[father[x]]] = 3;
			tag[father[x]] = 2;
			tag[x] = 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}