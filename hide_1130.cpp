#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 50004;
int n, head[MaxN], cntEdge, f[MaxN];
int dis[15][MaxN][2], siz[15][MaxN][2];
int len[MaxN], digit[MaxN][15], maxlen;
struct Edge{
	int destination, nextEdge;
}edge[MaxN];

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

inline int DFS(int d, int x, int mul){
	int res = 0;
	siz[d][x][digit[x][d]] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		res += DFS(d, y, mul);
		res += (dis[d][y][1] * siz[d][x][0] + dis[d][x][0] * siz[d][y][1] + siz[d][y][1] * siz[d][x][0]) * mul;
		res += (dis[d][y][0] * siz[d][x][1] + dis[d][x][1] * siz[d][y][0] + siz[d][y][0] * siz[d][x][1]) * mul;
		dis[d][x][1] += dis[d][y][1] + siz[d][y][1];
		dis[d][x][0] += dis[d][y][0] + siz[d][y][0];
		siz[d][x][1] += siz[d][y][1];
		siz[d][x][0] += siz[d][y][0];
	}
	return res;
}

signed main(){
	n = Read();
	for(int i=2; i<=n; i++){
		f[i] = Read();
		AddEdge(f[i], i);
	}
	for(int i=1; i<=n; i++){
		int a = Read();
		while(a){
			len[i]++;
			digit[i][len[i]] = a & 1;
			a >>= 1;
			maxlen = max(maxlen, len[i]);
		}
	}
	int mul = 1, ans = 0;
	for(int i=1; i<=maxlen; i++){
		ans += DFS(i, 1, mul);
		mul<<=1;
	}
	printf("%lld", ans);
	return 0;
}