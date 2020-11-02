#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 50005;
int T, n, k, a[MaxN];

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
//	freopen("coin.in", "r", stdin);
//	freopen("coin.out", "w", stdout);
	T = Read();
	while(T--){
		n = Read(), k = Read();
		for(int i=1; i<=n; i++)
			a[i] = Read();
		sort(a+1, a+1+n);
		int mx = 0, sum = 0;
		if(k) mx = a[n];
		for(int i=1; i<=n-k; i++)
			sum += a[i];
		printf("%lld\n", max(sum, mx));
	}
	return 0;
}