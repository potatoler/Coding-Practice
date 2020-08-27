#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
const int MaxN = 1003, MaxM = 202, Mod = 1000000007;
int f[2][MaxM][MaxM][2];
char a[MaxN], b[MaxM];
int n, m, k;
bool val = 1;

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

int main(){
	n = Read(), m = Read(), k = Read();
	scanf("%s%s",a+1, b+1);
	f[0][0][0][0] = f[1][0][0][0] = 1;
		for(int i=1; i<=n; i++, val^=1)
			for(int j=1; j<=m; j++)
				for(int p=1; p<=k; p++){
					if(a[i] == b[j]){
						f[val][j][p][0] = (f[val^1][j][p][0] + f[val^1][j][p][1]) % Mod;
						f[val][j][p][1] = (f[val^1][j-1][p][1] + 
										(f[val^1][j-1][p-1][0] + f[val^1][j-1][p-1][1]) % Mod) % Mod;
					}
					else{
						f[val][j][p][0] = (f[val^1][j][p][0] + f[val^1][j][p][1]) % Mod;
						f[val][j][p][1] = 0;
					}
				}
	printf("%d\n", (f[n&1][m][k][0] + f[n&1][m][k][1]) % Mod);
	return 0;
}