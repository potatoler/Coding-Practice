#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, a[MaxN], b[MaxN], ans, sum[MaxN], sa[MaxN], sb[MaxN], mix[MaxN], stamp=-1;

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(op == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=n; i++)
		b[i] = Read();
	for(int i=n; i>=1; i--){
		sum[i] = sum[i+1] + a[i] + b[i];
		sb[i] = sb[i+1] + sum[i+1] + b[i] + b[i] * ((n-i)<<1);
		sa[i] = sa[i+1] + sum[i+1] + b[i] + a[i+1] * ((n-i)<<1);
	}
	for(int i=3; i<=n; i+=2)
		mix[i] = mix[i-2] + a[i-2] * (++stamp) + b[i-2] * (++stamp) + b[i-1] * (++stamp) + a[i-1] * (++stamp);
	for(int i=1; i<=n; i+=2){
		ans = max(ans, mix[i] + sb[i] + sum[i] * ((i<<1)-2));
		ans = max(ans, mix[i] + sa[i] + sum[i] * ((i<<1)-2));
	}
	printf("%lld", ans);
	return 0;
}