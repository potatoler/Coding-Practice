#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,e[210],f[210][210],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i]);
		e[i+n]=e[i];//破环成链
	}
	for(int i=2;i<=n*2;i++)
		for(int j=i-1;i-j<n&&j;j--){
			for(int k=j;k<i;k++)
				f[j][i]=max(f[j][i],f[j][k]+f[k+1][i]+e[j]*e[k+1]*e[i+1]);
			if(f[j][i]>ans) ans=f[j][i];
		}
	printf("%d",ans);
	return 0;
}