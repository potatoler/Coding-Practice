#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int m,n,ans;

int gcd(int x,int y){
	if(!y) return x;
	return gcd(y,x%y);
}

int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
		ans += pow(m, gcd(n,i));
	if(n&1) ans += n * pow(m, (n+1)/2);
	else ans += (n/2) * pow(m, (n+2)/2) + (n/2) * pow(m,n/2);
	printf("%d\n",ans/(n*2));
	return 0;
}