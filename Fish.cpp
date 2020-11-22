#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
double a[20][20], f[1<<20];

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
	int n = Read();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			scanf("%lf", &a[i][j]);
	f[(1<<n)-1] = 1;
	for(int i = (1<<n)-2; i; i--){
		int cnt = 0, tmp = i;
		while(tmp){
			cnt += (tmp & 1);
			tmp >>= 1;
		}
		for(int j=1; j<=n; j++){
			if((1<<(j-1)) & i) continue;
			for(int k=1; k<=n; k++){
				if(!((1<<(k-1)) & i)) continue;
				f[i] += f[i|(1<<(j-1))] * a[k][j] / (double)(cnt * (cnt+1) / 2);
			}
		}
	}
	for(int i=1; i<=n; i++)
		printf("%.6lf ", f[1<<(i-1)]);
	return 0;
}