#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=1000005;
int n,k,bl,cl;
ll ans,a[maxn],b[maxn],c[maxn],maxSum,thisSum,tmpSum,mx=-1000005;
bool cmp(int x,int y){return x>y;}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		mx=max(mx,a[i]);
		if(a[i]>=0&&a[i-1]>=0) tmpSum+=a[i];
		if(a[i]<0&&a[i-1]>=0){
			b[++bl]=tmpSum;
			//printf("%lld ",tmpSum);
			tmpSum=0;
			c[++cl]=a[i];
		}
		if(a[i]<0&&a[i-1]<0) c[++cl]=a[i];
		if(a[i]>=0&&a[i-1]<0){
			if(cl>=k){sort(c+1,c+1+cl,cmp);
			int amt=cl%k?cl/k+1:cl/k;
			for(int i=1;i<=amt;i++)
				tmpSum+=c[i];
			b[++bl]=tmpSum;
			//printf("%lld ",tmpSum);
			}
			tmpSum=a[i];
			cl=0;
		}
	}
	b[++bl]=tmpSum;
	for(int i=1;i<=bl;i++){
		thisSum+=b[i];
		if(thisSum>maxSum) maxSum=thisSum;
		else if(thisSum<0) thisSum=0;
	}
	if(maxSum==0&&bl==2) maxSum=mx;
	//for(int i=1;i<=cl;i++) printf("%lld ",c[i]);printf("\n");
	//for(int i=1;i<=bl;i++) printf("%lld ",b[i]);
	//printf("%lld ",mx);
	printf("%lld",maxSum);
}