#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100005;
const int zahyo=33333;
int n,x[zahyo],y[zahyo],ans[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++){
		int tot=0;
		for(int j=1;j<=n;j++)
			if(x[j]<=x[i]&&y[j]<=y[i]&&i!=j) tot++;
		ans[tot]++;
	}
	for(int i=0;i<n;i++)
		printf("%d\n",ans[i]);
	return 0;
}