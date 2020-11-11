#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 10004;
int n,m,k, ans;
bool block[MaxN][MaxN], visited[MaxN][MaxN][5];

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

inline void DFS(int x, int y, int w){
	if(visited[x][y][w]){
		printf("%lld", ans);
		exit(0);
	}
	if(!visited[x][y][1] && !visited[x][y][2] && !visited[x][y][3] && !visited[x][y][4]) ans++;
	visited[x][y][w] = true;
	switch(w){
		case 1:{
			if(!block[x-1][y+1]){
				DFS(x-1, y+1, 1);
				return;
			}
			if((block[x-1][y] && block[x][y+1]) || (!block[x-1][y] && !block[x][y+1])){
				DFS(x, y, 4);
				return;
			}
			if(block[x-1][y]){
				DFS(x, y+1, 3);
				return;
			}
			if(block[x][y+1]){
				DFS(x-1, y, 2);
				return;
			}
			break;
		}
		case 2:{
			if(!block[x-1][y-1]){
				DFS(x-1, y-1, 2);
				return;
			}
			if((block[x][y-1] && block[x-1][y]) || (!block[x][y-1] && !block[x-1][y])){
				DFS(x, y, 3);
				return;
			}
			if(block[x][y-1]){
				DFS(x-1, y, 1);
				return;
			}
			if(block[x-1][y]){
				DFS(x, y-1, 4);
				return;
			}
			break;
		}
		case 3:{
			if(!block[x+1][y+1]){
				DFS(x+1, y+1, 3);
				return;
			}
			if((block[x+1][y] && block[x][y+1]) || (!block[x+1][y] && !block[x][y+1])){
				DFS(x, y, 2);
				return;
			}
			if(block[x+1][y]){
				DFS(x, y+1, 1);
				return;
			}
			if(block[x][y+1]){
				DFS(x+1, y, 4);
				return;
			}
			break;
		}
		case 4:{
			if(!block[x+1][y-1]){
				DFS(x+1, y-1, 4);
				return;
			}
			if((block[x+1][y] && block[x][y-1]) || (!block[x+1][y] && !block[x][y-1])){
				DFS(x, y, 1);
				return;
			}
			if(block[x+1][y]){
				DFS(x, y-1, 2);
				return;
			}
			if(block[x][y-1]){
				DFS(x+1, y, 3);
				return;
			}
		}
	}
}

signed main(){
	n = Read(), m = Read(), k = Read();
	for(int i=1; i<=k; i++){
		int x = Read(), y = Read();
		block[x][y] = true;
	}
	int x = Read(), y = Read();
	char ch[5];
	scanf("%s", ch+1);
	for(int i=0; i<=n+1; i++)
		block[i][0] = block[i][m+1] = true;
	for(int i=0; i<=m+1; i++)
		block[0][i] = block[n+1][i] = true;
	if(ch[1] == 'N' && ch[2] == 'E') DFS(x, y, 1);
	else if(ch[1] == 'N' && ch[2] == 'W') DFS(x, y, 2);
	else if(ch[1] == 'S' && ch[2] == 'E') DFS(x, y, 3);
	else DFS(x, y, 4);
	return 0;
}
