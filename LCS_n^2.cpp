#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=100005;
int f[maxn],a[maxn],b[maxn],n;
int x,y;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		x=0;
		for(int j=1;j<=n;j++){
			y=f[j];
			if(a[i]==b[j]) f[j]=x+1;
			else if(f[j-1]>f[j]) f[j]=f[j-1];
			x=y;
		}
	}
	printf("%d\n",f[n]);
	return 0;
}