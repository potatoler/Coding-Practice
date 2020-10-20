#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<map>
#include<vector>
using namespace std;
const int MaxN = 302;
int n, f[MaxN*2][MaxN][MaxN], value[MaxN][MaxN];

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

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			value[i][j] = Read();
	memset(f, -0x3f, sizeof(f));
	f[1][1][1] = value[1][1];
	for(int i=2; i<n+n; i++)
		for(int j=1; j<=n; j++)
			if(i-j+1>=1 && i-j+1<=n)
				for(int k=1; k<=n; k++)
					if(i-k+1>=1 && i-k+1<=n){
						int tmp;
						tmp = j==k? value[j][i-j+1] : value[j][i-j+1] + value[k][i-k+1];
						f[i][j][k] = max(f[i][j][k], f[i-1][j][k] + tmp);
						f[i][j][k] = max(f[i][j][k], f[i-1][j-1][k-1] + tmp);
						f[i][j][k] = max(f[i][j][k], f[i-1][j-1][k] + tmp);
						f[i][j][k] = max(f[i][j][k], f[i-1][j][k-1] + tmp);
					}
	printf("%d", f[n+n-1][n][n]);
	return 0;
}