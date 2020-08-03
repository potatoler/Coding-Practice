#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int k[10],p[10],x[10];
int n,m,cnt,ans;
void dfs(int d){
	if(d==n+1){
		if(ans==0){
			cnt++;
			return;
		}
		else return;
	}
	for(int i=1;i<=m;i++){
		int tmp=k[d]*pow(i,p[d]);
		ans+=tmp;
		dfs(d+1);
		ans-=tmp;
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&k[i],&p[i]);
	dfs(1);
	printf("%d",cnt);
}