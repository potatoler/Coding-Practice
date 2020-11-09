#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2000006;
int n, k, q, a[MaxN], sum[MaxN];

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
	n = Read(), k = Read(), q = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		int cur = a[i] != a[i-1] ? 1 : 0;
		sum[i] = sum[i-1] + cur;
	}
	while(q--){
		int l = Read(), r = Read();
		int ans = sum[r] - sum[l-1];
		if(sum[l]-sum[l-1] == 0) ans++;
//		printf("%lld ", ans);
		printf(ans>=k? "Yes\n" : "No\n");
	}
	return 0;
}