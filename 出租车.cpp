#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<set>
//#define int long long
using namespace std;
const int MaxN = 2003;
int n, k, u[MaxN], v[MaxN], f[MaxN][11][11][11][11];

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

inline int DFS(int cnt, int pos, int a, int b, int c){
	if(f[cnt][pos][a][b][c] != -1) return f[cnt][pos][a][b][c];
	int res = INT_MAX;
	if(a) res = min(res, DFS(cnt, a, 0, b, c) + abs(pos-a) + 1);
	if(b) res = min(res, DFS(cnt, b, a, 0, c) + abs(pos-b) + 1);
	if(c) res = min(res, DFS(cnt, c, a, b, 0) + abs(pos-c) + 1);
	if(cnt > n){
		if(!a && !b && !c) return 0;
		return f[cnt][pos][a][b][c] = res;
	}
	if(a && b && c){
		res = min(res, DFS(cnt+1, v[cnt], a, b, c) + abs(pos-u[cnt]) + abs(u[cnt]-v[cnt]) + 2);
		res = min(res, DFS(cnt+1, a, v[cnt], b, c) + abs(pos-u[cnt]) + abs(u[cnt] - a) + 2);
		res = min(res, DFS(cnt+1, b, a, v[cnt], c) + abs(pos-u[cnt]) + abs(u[cnt] - b) + 2);
		res = min(res, DFS(cnt+1, c, a, b, v[cnt]) + abs(pos-u[cnt]) + abs(u[cnt] - c) + 2);
	}
	else{
		if(!a) res = min(res, DFS(cnt+1, u[cnt], v[cnt], b, c) + abs(pos-u[cnt]) + 1);
		else if(!b) res = min(res, DFS(cnt+1, u[cnt], a, v[cnt], c) + abs(pos-u[cnt]) + 1);
		else res = min(res, DFS(cnt+1, u[cnt], a, b, v[cnt]) + abs(pos-u[cnt]) + 1);
	}
	return f[cnt][pos][a][b][c] = res;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++)
		u[i] = Read(), v[i] = Read();
	memset(f, -1, sizeof(f));
	int ans = DFS(1, 1, 0, 0, 0);
	printf("%d", ans);
	return 0;
}