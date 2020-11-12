#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 502;
int n, m, a[MaxN][MaxN], b[MaxN][MaxN];
char ab[MaxN][MaxN];

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
	for(int i=1; i<=n; i++)
		scanf("%s", ab[i]+1);
	for(int i=1; i<=n; i++){
		a[i][1] = b[i][m] = 1;
		if(i & 1)
			for(int j=2; j<m; j++)
				a[i][j] = 1;
		else
			for(int j=2; j<m; j++)
				b[i][j] = 1;
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(ab[i][j] == '1') a[i][j] = b[i][j] = 1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			printf("%lld", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			printf("%lld", b[i][j]);
		}
		printf("\n");
	}
}