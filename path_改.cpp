#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1000006, MaxM = 2000006, Mod = 1000000007;
int n, m, head[2][MaxN], cnt[2], dis[MaxN], ver[MaxN], tot;
struct Edge{
	int destination, nextEdge;
}edge[2][MaxM];
queue<int> q;

inline void AddEdge(int u, int v, int w){
	cnt[w]++;
	edge[w][cnt[w]] = {v, head[w][u]};
	head[w][u] = cnt[w];
	return;
}

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

signed main(){
//	freopen("path.in", "r", stdin);
//	freopen("path.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
	}
	q.push(1);
	for(int i=0; i<MaxN; i++)
		dis[i] = 0x3f3f3f3f;
	dis[1] = 0;
	while(q.size()){
		int x = q.front();
		q.pop();
		for(int i = head[0][x]; i; i = edge[0][i].nextEdge){
			int y = edge[0][i].destination;
			if(dis[y]){
				dis[y] = 0;
				q.push(y);
			}
		}
	}
	for(int i=1; i<=n; i++)
		if(!dis[i]) q.push(i);
	while(q.size()){
		tot=1;
		ver[tot] = q.front();
		q.pop();
		while(q.size() && dis[q.front()] == dis[ver[1]]){
			ver[++tot] = q.front();
			q.pop();
		}
		for(int i=1; i<=tot; i++){
			int tmp = dis[ver[i]] * 2 % Mod;
			for(int j = head[0][ver[i]]; j; j = edge[0][j].nextEdge){
				int &y = edge[0][j].destination;
				if(dis[y] == 0x3f3f3f3f){
					dis[y] = tmp;
					q.push(y);
				}
			}
		}
		for(int i=1; i<=tot; i++){
			int tmp = (dis[ver[i]] * 2 + 1) % Mod;
			for(int j = head[1][ver[i]]; j; j = edge[1][j].nextEdge){
				int &y = edge[1][j].destination;
				if(dis[y] == 0x3f3f3f3f){
					dis[y] = tmp;
					q.push(y);
				}
			}
		}
	}
	for(int i=2; i<=n; i++){
		if(dis[i] == 0x3f3f3f3f) printf("-1 ");
		else printf("%d ", dis[i]);
	}
	return 0;
}