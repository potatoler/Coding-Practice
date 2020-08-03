#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=50005;
char c[maxn][4];
int sum,n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",c[i]);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++){
			int cnt=0;
			for(int p=0;p<4;p++)
				if(c[i][p]==c[j][p]) cnt++;
			if(cnt==m) sum++;
		}
	printf("%d\n",sum);
	return 0;
}