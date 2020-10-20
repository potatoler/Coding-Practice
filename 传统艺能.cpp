#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1000006, Mod = 998244353;
int n, a[MaxN], lst, sum;

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

inline int QuickPower(int x, int k){
	int res = 1;
	while(k){
		if(k&1) res = res * x % Mod;
		x = x * x % Mod;
		k >>= 1;
	}
	return res;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	sort(a+1, a+1+n);
	for(int i=1; i<=n; i++){
		if(a[i] != a[i-1]) lst = i-1;
		sum = (sum + lst) % Mod;
	}
	int ans = sum * QuickPower((n-1)*2, Mod-2) % Mod;
	printf("%lld", ans);
	return 0;
}