#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int R,B;
double f[2][5005];//rolling array —— am I callingh the right name?
int main(){
	scanf("%d%d",&R,&B);
	for(int i=1;i<=R;i++){
		f[i&1][0]=i; 
		for(int j=1;j<=B;j++){
			f[i&1][j]=max((f[i&1][j-1]-1) * (double)(j) / (double)(i+j) + (f[i&1^1][j]+1) * (double)(i) / (double)(i+j), 0.0);
		}
	}
	printf("%0.6lf", f[R&1][B] - (5e-7));//prevent rounding
	return 0;
}