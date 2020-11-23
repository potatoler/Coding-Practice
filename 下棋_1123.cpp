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
const int Mod = 1000000007;
int n, m, k, f[155][155][25][25];

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

inline int DFS(int i, int j, int p, int q){
	if(i == n && j == m) return 1;
	if(f[i][j][p][q] != -1) return f[i][j][p][q];
	int res = 0;
	if(i<n && p<k) res = (res + DFS(i+1, j, p+1, max(0,q-1))) % Mod;
	if(j<m && q<k) res = (res + DFS(i, j+1, max(0,p-1), q+1)) % Mod;
	return f[i][j][p][q] = res % Mod;
}

signed main(){
	n = Read(), m = Read(), k = Read();
	memset(f, -1, sizeof(f));
	int ans = DFS(0, 0, 0, 0);
	printf("%d", ans);
	return 0;
}