#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int MaxN = 1005;
int n, m, a[MaxN][MaxN], cnt;

inline bool OK(int x1, int y1, int x2, int y2){
	int l = x2 - x1 + 1;
	if(l%2 == 0){
		for(int i=0;i<=l-1;i++){
			for(int j=0;j<=l/2-1;j++){
				if(a[x1+i][y1+j] != a[x2-i][y2-j]) return false;
			}
		}
	}
	else if(l%2 == 1){
		for(int i=0;i<=l-1;i++){
			for(int j=0;j<=l/2;j++){
				if(a[x1+i][y1+j] != a[x2-i][y2-j]) return false;
			}
		}
	}
	return true;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int l=1;(i+l-1<=n&&j+l-1<=m);l++){
				if(OK(i, j, i+l-1, j+l-1)) cnt++;
			}
		}
	}
//	if(OK(1,1,n,m)) printf("OK");
//	else printf("NOT");
	printf("%d",cnt);
}