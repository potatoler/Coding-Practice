#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003;
int n, m, val[MaxN][MaxN], f[MaxN][MaxN][3];

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

inline int Tri_Max(int a, int b, int c){
	return max(a,max(b,c));
}

inline int DP(int x, int y, int d){
	if(x == 1 && y == 1) return val[x][y];
	if(x < 1 || x > n || y < 1 || y > m) return -INT_MAX;
	if(f[x][y][d]) return f[x][y][d];
	switch(d){
		case 0:{
			return f[x][y][d] = Tri_Max(DP(x,y-1,0), DP(x,y-1,1), DP(x,y-1,2)) + val[x][y];
			break;
		}
		case 1:{
			return f[x][y][d] = max(DP(x-1,y,1), DP(x-1,y,0)) + val[x][y];
			break;
		}
		case 2:{
			return f[x][y][d] = max(DP(x+1,y,2), DP(x+1,y,0)) + val[x][y];
		}
	}
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			val[i][j] = Read();
	printf("%lld\n", max(DP(n,m,0), DP(n,m,1)));
	return 0;
}