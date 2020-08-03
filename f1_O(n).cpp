#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,sum,tmp;
int main(){
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		tmp=i;
		while(0==tmp%2) tmp/=2;
		sum+=tmp;
	}
	printf("%lld",sum);
	return 0;
}