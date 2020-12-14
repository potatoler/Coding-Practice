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
using namespace std;
const int MaxN = 1101 * 22 + 10, MaxM = (MaxN + 1100 + 13 * 1101 + 10) * 2;
int n, m, k, s, t, head[MaxN], cntEdge;
int dep[MaxN], cur[MaxN];
struct Edge{
	int destination, nextEdge, capacity;
}edge[MaxM];
struct Bus{
	int size, cnt, station[30];
}bus[30];
int father[30];
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

inline int Find(int x){
	return father[x] == x ? x : father[x] = Find(father[x]);
}

inline int Serial(int id, int day){
	return day * (n+2) + id;
}

inline void AddBranch(int u, int v, int c){
	edge[cntEdge] = {v, head[u], c};
	head[u] = cntEdge++;
	edge[cntEdge] = {u, head[v], 0};
	head[v] = cntEdge++;
	return;
}

inline bool BFS(){
	while(q.size()) q.pop();
	memset(dep, -1, sizeof(dep));
	q.push(s), cur[s] = head[s], dep[s] = 0;
	while(q.size()){
		int x = q.front();
		q.pop();
		for(int i = head[x]; ~i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(dep[y] == -1 && edge[i].capacity){
				dep[y] = dep[x] + 1;
				cur[y] = head[y];
				if(y == t) return true;
				q.push(y);
			}
		}
	}
	return false;
}

inline int DFS(int x, int limit){
	if(x == t) return limit;
	int flow = 0;
	for(int i = cur[x]; ~i && flow < limit; i = edge[i].nextEdge){
		int y = edge[i].destination;
		cur[x] = i;
		if(dep[y] == dep[x] + 1 && edge[i].capacity){
			int avi = DFS(y, min(edge[i].capacity, limit - flow));
			if(!avi) dep[y] = -1;
			edge[i].capacity -= avi;
			edge[i^1].capacity += avi;
			flow += avi;
		}
	}
	return flow;
}

inline int Dinic(){
	int res = 0, flow = 0;
	while(BFS()){
		while(flow = DFS(s, INT_MAX)) res += flow;
	}
	return res;
}

signed main(){
	n = Read(), m = Read(), k = Read();
	s = MaxN-2, t = MaxN-1;
	memset(head, -1, sizeof(head));
	for(int i=0; i<30; i++)
		father[i] = i;
	for(int i=0; i<m; i++){
		int h = Read(), r = Read();
		bus[i].size = h, bus[i].cnt = r;
		for(int j=0; j<r; j++){
			int ID = Read();
			if(ID == -1) ID = n+1;
			bus[i].station[j] = ID;
			if(j){
				int x = bus[i].station[j-1];
				father[Find(x)] = Find(ID);
			}
		}
	}
	if(Find(0) != Find(n+1)) printf("0\n");
	else{
		AddBranch(s, Serial(0,0), k);
		AddBranch(Serial(n+1,0), t, INT_MAX);
		int day = 1, res = 0;
		while(true){
			AddBranch(Serial(n+1,day), t, INT_MAX);
			for(int i=0; i<=n+1; i++)
				AddBranch(Serial(i,day-1), Serial(i,day), INT_MAX);
			for(int i=0; i<m; i++){
				int r = bus[i].cnt,
					las = bus[i].station[(day-1) % r],
					now = bus[i].station[day % r];
				AddBranch(Serial(las,day-1), Serial(now,day), bus[i].size);
			}
			res += Dinic();
//			printf("%d\n", res);
			if(res >= k) break;
			day++;
		}
		printf("%d", day);
	}
}