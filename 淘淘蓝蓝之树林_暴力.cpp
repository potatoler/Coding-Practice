#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2003;
char mp[MaxN][MaxN];
int n, m, cnt, x[5], y[5], ans, dis[5][5], pos;

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

inline void Input(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		scanf("%s", mp[i]+1);
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			printf("%c", mp[i][j]);
//		}
//		printf("\n");
//	}
	return;
}

inline void Find(){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(mp[i][j] == 'X'){
				if(cnt == 0) x[1] = i, y[1] = j;
				cnt++;
				x[3] = i, y[3] = j;
			}
		}
	}
	cnt = 0;
	for(int j=1; j<=m; j++){
		for(int i=1; i<=n; i++){
			if(mp[i][j] == 'X'){
				if(cnt == 0) x[2] = i, y[2] = j;
				cnt++;
				x[4] = i, y[4] = j;
			}
			if(mp[i][j] == '*') x[0] = i, y[0] = j;
		}
	}
	x[1] -= 1;
	y[2] -= 1;
	x[3] += 1;
	y[4] += 1;
	if(y[0] <= y[1] && x[0] <= x[2]) pos = 1;
	else if(y[0] <= y[3] && x[0] >= x[2]) pos = 2;
	else if(y[0] >= y[3] && x[0] >= x[4]) pos = 3;
	else if(y[0] >= y[1] && x[0] <= x[4]) pos = 4;
//	for(int i=1; i<=4; i++)
//		printf("%lld %lld\n", x[i], y[i]);
	return;
}

inline void DFS(int type, int fr, int to, int xx, int yy, int step = 0){
	if(xx == x[to] && yy == y[to]){
		ans = min(ans, step);
		return;
	}
	switch(type){
		case 1:{
			if(mp[xx+1][yy] != 'X' && xx+1 <= n) DFS(1, fr, to, xx+1, yy, step+1);
			if(mp[xx+1][yy-1] != 'X' && xx+1 <= n && yy-1 >= 1) DFS(1, fr, to, xx+1, yy-1, step+1);
			if(mp[xx][yy-1] != 'X' && yy-1 >= 1) DFS(1, fr, to, xx, yy-1, step+1);
			break;
		}
		case 2:{
			if(mp[xx+1][yy] != 'X' && xx+1 <= n) DFS(2, fr, to, xx+1, yy, step+1);
			if(mp[xx+1][yy+1] != 'X' && xx+1 <= n && yy+1 <= m) DFS(2, fr, to, xx+1, yy+1, step+1);
			if(mp[xx][yy+1] != 'X' && yy+1 <= m) DFS(2, fr, to, xx, yy+1, step+1);
			break;
		}
		case 3:{
			if(mp[xx-1][yy] != 'X' && xx-1 >= 1) DFS(3, fr, to, xx-1, yy, step+1);
			if(mp[xx-1][yy+1] != 'X' && xx-1 >= 1 && yy+1 <= m) DFS(3, fr, to, xx-1, yy+1, step+1);
			if(mp[xx][yy+1] != 'X' && yy+1 <= m) DFS(3, fr, to, xx, yy+1, step+1);
			break;
		}
		case 4:{
			if(mp[xx-1][yy] != 'X' && xx-1 >= 1) DFS(4, fr, to, xx-1, yy, step+1);
			if(mp[xx-1][yy-1] != 'X' && xx-1 >= 1 && yy+1 >= 1) DFS(4, fr, to, xx-1, yy-1, step+1);
			if(mp[xx][yy-1] != 'X' && yy-1 >= 1) DFS(4, fr, to, xx, yy-1, step+1);
			break;
		}
	}
}

inline void Work(){
	int res = INT_MAX;
	ans = INT_MAX;
	DFS(1, 1, 2, x[1], y[1]);
	dis[1][2] = ans;
	ans = INT_MAX;
	DFS(2, 2, 3, x[2], y[2]);
	dis[2][3] = ans;
	ans = INT_MAX;
	DFS(3, 3, 4, x[3], y[3]);
	dis[3][4] = ans;
	ans = INT_MAX;
	DFS(4, 4, 1, x[4], y[4]);
	dis[4][1] = ans;
	switch(pos){
		case 1:{
			ans = INT_MAX;
			DFS(4, 1, 0, x[1], y[1]);
			dis[1][0] = ans;
			ans = INT_MAX;
			DFS(4, 2, 0, x[2], y[2]);
			dis[2][0] = ans;
			res = dis[2][3] + dis[3][4] + dis[4][1] + min(dis[1][0]+dis[2][0], min(dis[1][2]+dis[2][0]*2, dis[1][2]+dis[1][0]*2));
			break;
		}
		case 2:{
			ans = INT_MAX;
			DFS(1, 2, 0, x[2], y[2]);
			dis[2][0] = ans;
			ans = INT_MAX;
			DFS(1, 3, 0, x[3], y[3]);
			dis[3][0] = ans;
			res = dis[1][2] + dis[4][1] + dis[3][4] + min(dis[2][0]+dis[3][0], min(dis[2][3]+dis[2][0]*2, dis[2][3]+dis[3][0]*2));
			break;
		}
		case 3:{
			ans = INT_MAX;
			DFS(2, 3, 0, x[3], y[3]);
			dis[3][0] = ans;
			ans = INT_MAX;
			DFS(2, 4, 0, x[4], y[4]);
			dis[4][0] = ans;
			res = dis[4][1] + dis[1][2] + dis[2][3] + min(dis[3][0]+dis[4][0], min(dis[3][4]+dis[3][0]*2, dis[3][4]+dis[4][0]*2));
			break;
		}
		case 4:{
			ans = INT_MAX;
			DFS(3, 4, 0, x[4], y[4]);
			dis[4][0] = ans;
			ans = INT_MAX;
			DFS(3, 1, 0, x[1], y[1]);
			dis[1][0] = ans;
			res = dis[1][2] + dis[2][3] + dis[3][4] + min(dis[4][0]+dis[1][0], min(dis[4][1]+dis[4][0]*2, dis[4][1]+dis[1][0]*2));
			break;
		}
	}
	printf("%lld", res);
}

signed main(){
	Input();
	Find();
	Work();
}