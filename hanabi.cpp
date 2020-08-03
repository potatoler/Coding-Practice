#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int  maxn=100005;
int h[maxn],ans,cnt;
int op,l,r,a;
int main(){
	while(scanf("%d",&op)){
		if(op==0){
			ans=0;
			scanf("%d%d",&l,&r);
			for(int i=l;i<=r;i++)
				ans=max(ans,h[i]);
			printf("%d\n",ans);
		}
		if(op==1){
			scanf("%d",&a);
			for(int i=a+1;i<=cnt;i++)
				h[i-1]=h[i];
			cnt--;
		}
		if(op==2){
			scanf("%d",&a);
			h[++cnt]=a^ans;
		}
		if(op==-1) break;
	}
	return 0;
}