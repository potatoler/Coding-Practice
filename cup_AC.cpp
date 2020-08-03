//AC O(nlogn)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=100005;
int a[maxn*2],n,f[maxn*2];
int main(){
	scanf("%d",&n);
	if(n==0){
		printf("0");
		return 0;
	}
	int len=1;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[n+i]);
		a[n+1-i]=a[n+i];
	}
	f[1]=a[1];
	for(int i=2;i<=n*2;i++){
		if(a[i]>f[len]) f[++len]=a[i];
		else{
			int pos=lower_bound(f+1,f+len+1,a[i])-f;
			f[pos]=a[i];
		}
	}
	printf("%d\n",len);
}