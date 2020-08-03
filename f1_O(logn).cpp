#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
unsigned long long n;
unsigned long long sum(unsigned long long n) {
	if(n==1) return 1;
	if(n%2==0) return sum(n/2)+n*n/4;
	else return sum(n-1)+n; 
}
int main(){
	scanf("%llu",&n);
	printf("%llu",sum(n));
	return 0;
}