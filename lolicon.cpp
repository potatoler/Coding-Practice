#include<iostream>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int mod=100000007;
ll n,jc=1,f[1314521];
int main(){
	scanf("%lld",&n);
	if(n==1){
		printf("FBI open up!");
		return 0;
	}
	f[1]=0,f[2]=1;
	for(int i=3;i<=n;i++){
		f[i]=(i-1)*((f[i-1]+f[i-2])%mod);
		f[i]%=mod;
	}
	for(int i=1;i<=n;i++){
		jc*=i;
		jc%=mod;
	}
	f[n]%=mod;
	f[n]=f[n]*jc%mod;
	printf("%lld",f[n]);
	return 0;
}