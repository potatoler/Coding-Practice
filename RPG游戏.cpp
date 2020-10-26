#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1005;
int n, m, val[MaxN][MaxN], buff[MaxN][MaxN], f[MaxN][MaxN];

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
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			buff[i][j] = Read();
			f[i][j] = -1000000000;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			val[i][j] = Read();
		}
	}
	f[1][1] = 0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			for(int k=1; k<=i; k++){
				for(int l=1; l<=j; l++){
					if(i == k && j == l) continue;
					f[i][j] = max(f[i][j], f[k][l] + val[k][l] + buff[k][l] * (i-k+j-l));
				}
			}
		}
	}
	printf("%lld", f[n][m]);
	return 0;
}