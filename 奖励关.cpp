#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
double f[105][1 << 15];
int n, k, p[16], depend[16];
int main(){
	scanf("%d%d",&k,&n);
	const int AllSelect = (1<<n) - 1;
	for(int i=1;i<=n;i++){
		scanf("%d", &p[i]);
		int d;
		while(scanf("%d",&d) && d)
			depend[i] |= (1<<(d-1));
	}
	for(int i = k; i >= 1; i--){
		for(int con = 0; con <= AllSelect; con++){
			for(int j = 1; j <= n;j++){
				if((depend[j]&con) == depend[j]) f[i][con] += max(f[i+1][con], f[i+1][con | (1 << (j-1))]+p[j]);
				else f[i][con] += f[i+1][con];
			}
			f[i][con] /= n;
		}
	}
	printf("%.6lf",f[1][0]);
	return 0;
}