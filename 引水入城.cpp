#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#define int long long
#define nx x+xx[i]
#define ny y+yy[i]
using namespace std;
const int MaxN = 502;
int l[MaxN][MaxN], r[MaxN][MaxN];
int high[MaxN][MaxN];
int n,m;
bool vis[MaxN][MaxN];
int xx[4]={-1,0,1,0};
int yy[4]={0,1,0,-1};
int qx[MaxN*MaxN], qy[MaxN*MaxN];

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

inline void DFS(int x,int y){
	vis[x][y]=true;
	for (int i=0;i<4;i++){
		if (nx<1 || nx>n || ny<1 || ny>m) continue;
		if (high[nx][ny] >= high[x][y]) continue;
		if (!vis[nx][ny]) DFS(nx,ny);
		l[x][y] = min(l[x][y],l[nx][ny]);
		r[x][y] = max(r[x][y],r[nx][ny]);
	}
}

signed main(){
	n=Read();
	m=Read();
	memset(vis,false,sizeof(vis));
	memset(l,0x3f,sizeof(l));
	memset(r,0,sizeof(r));
	for (int i=1; i<=m; i++)
		l[n][i] = r[n][i] = i;
	for (int i=1; i<=n; i++)
		for (int j=1;j<=m;j++)    
			high[i][j] = Read();
	for (int i=1; i<=m; i++)
		if (!vis[1][i]) DFS(1,i);
	bool flag = false;
	int cnt = 0;
	for (int i=1; i<=m; i++)    
		if (!vis[n][i]){
			flag = true;
			cnt++;
		}
	if (flag){
		printf("0\n%lld",cnt);
		return 0;
	}
	int left = 1;
	while (left <= m){
		int maxr = 0;
		for (int i=1; i<=m; i++)
			if (l[1][i] <= left)
				maxr = max(maxr, r[1][i]);
		cnt++;
		left = maxr+1;
	}
	printf("1\n%lld",cnt);
}