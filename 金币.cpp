#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 6003;
int n, m, value[MaxN][MaxN], ans[MaxN * MaxN], cnt;
char map[MaxN][MaxN];
bool visited[MaxN][MaxN];

inline void DFS(int x, int y){
	visited[x][y] = true;
	if(value[x][y+1] && !visited[x][y+1]){
		DFS(x, y+1);
		value[x][y] += value[x][y+1];
		value[x][y+1] = 0;
	}
	if(value[x+1][y] && !visited[x+1][y]){
		DFS(x+1, y);
		value[x][y] += value[x+1][y];
		value[x+1][y] = 0;
	}
	if(value[x-1][y] && !visited[x-1][y]){
		DFS(x-1, y);
		value[x][y] += value[x-1][y];
		value[x-1][y] = 0;
	}
	if(value[x][y-1] && !visited[x][y-1]){
		DFS(x, y-1);
		value[x][y] += value[x][y-1];
		value[x][y-1] = 0;
	}
	return;
}

signed main(){
	scanf("%d%d", &m, &n);
	for(int i=1; i<=n; i++)
		scanf("%s", map[i]+1);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			value[i][j] = map[i][j] - '0';
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(!visited[i][j] && map[i][j] != '0') DFS(i,j);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(value[i][j]) ans[++cnt] = value[i][j];
	sort(ans+1, ans+1+cnt);
	printf("%d\n", cnt);
	for(int i=cnt; i; i--)
		printf("%d ", ans[i]);
}