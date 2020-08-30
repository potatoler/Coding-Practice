#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int a[10], b[10];

inline void Solve(int n, int m){
	int x = n / 10, y = n % 10;
	int tmp = x;
	for(int i=1; i<=y; i++)
		b[i] += m;
	for(int i=0; i<=9; i++)
		b[i] += m * x;
	while(tmp){
		b[tmp%10] += m * (y+1);
		tmp /= 10;
	}
	if(x) Solve(x-1, m*10);
}

signed main(){
	int l, r;
	while(scanf("%lld%lld", &l, &r) && (l||r)){
		if(l > r) swap(l,r);
		memset(b, 0, sizeof(b));
		Solve(l-1, 1);
		for(int i=0; i<=9; i++)
			a[i] = b[i];
		memset(b, 0, sizeof(b));
		Solve(r, 1);
		for(int i=0; i<=8; i++)
			printf("%lld ", b[i]-a[i]);
		printf("%lld\n", b[9]-a[9]);
	}
	return 0;
}