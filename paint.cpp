#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=33;
int num,n,m;
int c[maxn],mapu[maxn][maxn];
bool jaaji(int t){
	for(int i=1;i<=n;i++)
		if(mapu[i][t]==1&&c[i]==c[t]) return false;
	return true;
}
void dfs(int t){
	if(t>n){
		num++;
		return;
	}
	else{
		for(int i=1;i<=m;i++){
			c[t]=i;
			if(jaaji(t)==true) dfs(t+1);
			c[t]=0;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	num=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&mapu[i][j]);
	dfs(1);
	if(num==0) printf("Poor +Q");
	else printf("%d\n",num);
	return 0;
}
// 5 4
// 0 1 1 1 0
// 1 0 1 1 1
// 1 1 0 1 0
// 1 1 1 0 1
// 0 1 0 1 0