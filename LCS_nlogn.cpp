#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100005;
int a[maxn],b[maxn],idx[maxn],f[maxn],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		idx[a[i]]=i;
		f[i]=0x3f3f3f3f;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	int len=0;
	f[0]=0;
	for(int i=1;i<=n;i++){
		int l=0,r=len;
		if(idx[b[i]]>f[len]) f[++len]=idx[b[i]];
		else{
			while(l<r){
				int mid=(l+r)/2;
				if(f[mid]>idx[b[i]]) r=mid;
				else l=mid+1;
			}
			f[l]=min(idx[b[i]],f[i]);
		}
	}
	printf("%d",len);
	return 0;
}