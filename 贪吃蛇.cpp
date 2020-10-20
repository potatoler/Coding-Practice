#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 102;
int n, m, t, q;
bool obstacle[MaxN][MaxN];
deque<pair<int,int> > snake;

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

inline bool Operation(int type){
	if(type == 1){
		char d[5];
		scanf("%s", d);
		int x = snake.back().first, y = snake.back().second;
		switch(d[0]){
			case 'U': {
				x -= 1;
				break;
			}
			case 'D': {
				x += 1;
				break;
			}
			case 'L': {
				y -= 1;
				break;
			}
			case 'R': {
				y += 1;
				break;
			}
		}
		if(x == 0 || x == n+1 || y == 0 || y == m+1) return false;
		if(obstacle[x][y]) return false;
		snake.push_back(make_pair(x,y));
		obstacle[x][y] = true;
		return true;
	}
	else{
		int x = snake.front().first, y = snake.front().second;
		obstacle[x][y] = false;
		snake.pop_front();
		return true;
	}
}

signed main(){
	n = Read(), m = Read(), t = Read(), q = Read();
	while(t--){
		int x = Read(), y = Read();
		obstacle[x][y] = true;
	}
	int sx = Read(), sy = Read();
	snake.push_back(make_pair(sx,sy));
	obstacle[sx][sy] = true;
	for(int i=1; i<=q; i++){
		int op = Read();
		if(!Operation(op)){
			printf("%d", i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}