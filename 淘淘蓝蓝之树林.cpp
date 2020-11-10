#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 2003;
char mp[MaxN][MaxN];
int n, m, sx, sy, xx, yy, dis[MaxN][MaxN];
const int dx[8] = {-1,-1,-1,0,0,1,1,1}, dy[8] = {-1,0,1,-1,1,-1,0,1};

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

inline void Dijstra(){
	for(int i=0; i<=n; i++)
		for(int j=0; j<=m; j++)
			dis[i][j] = INT_MAX;
	dis[sx][sy] = 0;
	queue<pair<int,int> > q;
	q.push(make_pair(sx, sy));
	while(q.size()){
		int x = q.front().first, y = q.front().second;
		q.pop();
		for(int i=0; i<8; i++){
			int nx = x + dx[i], ny = y + dy[i];
			if(nx>=1 && nx<=n && ny>=1 && ny<=m && dis[x][y]+1<dis[nx][ny] && mp[nx][ny]!='X'){
				dis[nx][ny] = dis[x][y]+1;
				q.push(make_pair(nx,ny));
			}
		}
	}
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		scanf("%s", mp[i]+1);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(mp[i][j] == '*') sx = i, sy = j;
			if(mp[i][j] == 'X' && !xx) xx = i, yy = j;
		}
	}
	for(int i=1; i<xx; i++)
		mp[i][yy] = 'X';
	Dijstra();
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++)
//			printf("%lld ", dis[i][j]);
//		printf("\n");
//	}
	int ans = INT_MAX;
		ans = min(ans, min(dis[xx-1][yy-1], min(dis[xx-2][yy-1], dis[xx][yy-1])) + min(dis[xx-1][yy+1], min(dis[xx-2][yy+1], dis[xx][yy+1])) + 2);
	printf("%lld", ans);
	return 0;
}