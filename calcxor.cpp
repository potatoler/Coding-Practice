#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, ans, p[MaxN], sum[MaxN];

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
//	freopen("calcxor.in", "r", stdin);
//	freopen("calcxor.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++)
		p[i] = Read();
	for(int i=1; i<n; i++)
		sum[i] = sum[i-1] ^ i;
	ans = p[1];
	for(int i=2; i<=n; i++)
		ans ^= p[i];
	for(int i=2; i<=n; i++){
		int turn = n / i, left = n % i;
		if(turn & 1) ans ^= sum[i-1];
		ans = ans ^ sum[left];
	}
	printf("%lld", ans);
	return 0;
}