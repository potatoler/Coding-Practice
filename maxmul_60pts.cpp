#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=50;
long long a[maxn],f[maxn][10];
int n,k;
char c;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		cin>>c;
		a[i]=c-'0';
	}
	f[1][0]=a[1];
	for(int i=1;i<=n;i++)
		for(int j=0;j<=min(i-1,k);j++){//前i个数至多只有i-1个乘号
			if(j==0) f[i][j]=f[i-1][j]*10+a[i];
			else for(int l=1;l<=i;l++){
				long long tmp=0;
				for(int r=l+1;r<=i;r++) tmp=tmp*10+a[r];
				f[i][j]=max(f[i][j],f[l][j-1]*tmp);
			}
		}
	printf("%lld",f[n][k]);
	return 0;
}