#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100;
int f[maxn],a[maxn],n;
int main(){
	int tmp;
	while(cin>>tmp){
		n++;
		a[n]=tmp;
	}
	f[0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			if(a[j]<a[i]) f[i]=max(f[i],f[j]+1);
	printf("%d\n",f[n]);
	return 0;
}