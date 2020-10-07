#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
int n;
signed main(){
	scanf("%lld", &n);
	printf("%lld\n", n);
	printf("%lld ", n);
	for(int i=1; i<=n; i++)
		printf("%lld ", i);
	printf("\n");
	for(int i=2; i<=n ;i++)
		printf("2 %lld %lld\n", i-1, i);
	return 0;
}