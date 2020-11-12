#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 998244353;

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

inline int QuickPower(int x, int y){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return res;
}

signed main(){
	int n = Read(), fac = 1;
	for(int i=1; i<=n; i++){
		int a = Read();
		fac = fac * a % Mod;
	}
	int ans = QuickPower(fac, Mod-2);
	printf("%lld", ans);
	return 0;
}