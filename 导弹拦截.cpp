#include<bits/stdc++.h>
using namespace std;
int a[100005],f1[100005],f2[100005],n=1,len1=1,len2=1;
int main(){
	while(cin>>a[n]) n++; n--;
	f1[1]=f2[1]=a[1];
	for(int i=2;i<=n;i++){
		if(f1[len1]>=a[i]) f1[++len1]=a[i];
		else f1[upper_bound(f1+1,f1+len1+1,a[i],greater<int>())-f1]=a[i];
		if(f2[len2]<a[i]) f2[++len2]=a[i];
		else f2[lower_bound(f2+1,f2+len2+1,a[i])-f2]=a[i];
	}
	printf("%d\n%d",len1,len2);
	return 0;
}