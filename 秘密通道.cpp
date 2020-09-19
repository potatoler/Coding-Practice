#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 502*502;
int n, m, sx, sy, ex, ey, cntEdge, head[MaxN*8], dist[MaxN*8];
int queue[MaxN], hd=1, tl = 1;
bool visited[MaxN];
char mp[502][502];

struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*8*2];

struct NextStep{
	int x, y, dis;
}nextStep[5];

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
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
}

inline bool cmp(NextStep a, NextStep b){
	return a.dis < b.dis;
}

inline int Serial(int x, int y){
	return (x-1) * m + y;
}

inline void MakeGraph(int x, int y){
	int tmp = Serial(x, y);
	if(mp[x-1][y] != '#') AddEdge(tmp, Serial(x-1, y), 1);
	if(mp[x+1][y] != '#') AddEdge(tmp, Serial(x+1, y), 1);
	if(mp[x][y-1] != '#') AddEdge(tmp, Serial(x, y-1), 1);
	if(mp[x][y+1] != '#') AddEdge(tmp, Serial(x, y+1), 1);
	int xx = x, yy = y;
	while(mp[xx][yy] != '#') xx--;
	nextStep[1] = (NextStep){xx+1, yy, x-xx};
	xx = x;
	while(mp[xx][yy] != '#') xx++;
	nextStep[2] = (NextStep){xx-1, yy, xx-x};
	xx = x;
	while(mp[xx][yy] != '#') yy--;
	nextStep[3] = (NextStep){xx, yy+1, y-yy};
	yy = y;
	while(mp[xx][yy] != '#') yy++;
	nextStep[4] = (NextStep){xx, yy-1, yy-y};
	yy = y;
	sort(nextStep+1, nextStep+1+4, cmp);
	AddEdge(tmp, Serial(nextStep[1].x, nextStep[1].y), nextStep[1].dis-1);
	AddEdge(tmp, Serial(nextStep[2].x, nextStep[2].y), nextStep[1].dis);
	AddEdge(tmp, Serial(nextStep[3].x, nextStep[3].y), nextStep[1].dis);
	AddEdge(tmp, Serial(nextStep[4].x, nextStep[4].y), nextStep[1].dis);
}

inline void SPFA(int st){
	for(int i=1; i<=n*m; i++)
		dist[i] = INT_MAX;
	dist[st] = 0;
	queue[tl++] = st;
	visited[st] = true;
	while(hd != tl){
		int top = queue[hd];
		hd++;
		visited[top] = 0;
		if(dist[top] == INT_MAX) continue;
		for(int i = head[top]; i; i = edge[i].nextEdge){
			int to = edge[i].destination;
			if(dist[to] > dist[top] + edge[i].value){
				dist[to] = dist[top] + edge[i].value;
				if(!visited[to]) visited[to] = true, queue[tl++] = to;
			}
		}
	}
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			cin >> mp[i][j];
			if(mp[i][j] == 'C') sx = i, sy = j;
			if(mp[i][j] == 'F') ex = i, ey = j;
		}
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(mp[i][j] != '#') MakeGraph(i, j);
	SPFA(Serial(sx, sy));
	if(dist[Serial(ex, ey)] == INT_MAX) printf("nemoguce");
	else printf("%d", dist[Serial(ex, ey)]);
	return 0;
}