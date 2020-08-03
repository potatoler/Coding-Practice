#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,W,cnt=1,f[maxn],w[maxn],v[maxn];
int main(){
	scanf("%d%d",&n,&W);
	for(int i=1;i<=n;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		for(int j=1;j<=c;j++){
			v[++cnt]=j*a;
			w[cnt]=j*b;
			c-=j;
		}
		if(c){
			v[++cnt]=a*c;
			w[cnt]=b*c;
		}
	}
	for(int i=1;i<=cnt;i++)
		for(int j=W;j>=w[i];j--)
			f[j]=max(f[j],f[j-w[i]]+v[i]);
	printf("%d\n",f[W]);
	return 0;
}