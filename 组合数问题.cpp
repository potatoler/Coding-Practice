#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
int n,k,r,p;
int c[110][110];
struct Node{
	int a[110];
}f;
Node operator * (Node x,Node y){
	Node ret;
	for(int i=0;i<100;i++)ret.a[i]=0;
	for(int i=0;i<k;i++)
		for(int j=0;j<k;j++)
			ret.a[i]=(ret.a[i]+x.a[j]*y.a[(i-j+k)%k])%p;
	return ret;
}

Node qpow(Node x,int y){
	Node ret=x;
	while(y){
		if(y%2==1)ret=ret*x;
		x=x*x;
		y>>=1;
	}
	return ret;
}

signed main(){
	scanf("%lld%lld%lld%lld",&n,&p,&k,&r);
	c[1][1]=1;
	for(int i=2;i<=k+1;i++)
		for(int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%p;
	for(int i=0;i<k;i++)
		f.a[i]=c[k+1][i+1];
	f.a[0]++;
	printf("%lld",qpow(f,n-1).a[r]%p);
	return 0;
}