#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 5000006;
int n, k, mx = -INT_MAX, a[MaxN], f[MaxN];

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
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		a[i] += a[i-1];
	}
	for(int i=1; i<=n; i++){
		if(i-k >= 0){
			mx = max(mx, f[i-k]-a[i-k]);
			f[i] = max(f[i-1], a[i] + mx);
		}
	}
	printf("%lld", f[n]);
	return 0;
}