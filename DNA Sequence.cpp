#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int a, b;

signed main(){
	scanf("%lld%lld", &a, &b);
	int x = (a+b) / 2, y = a - x;
	printf("%lld %lld", x, y);
	return 0;
}