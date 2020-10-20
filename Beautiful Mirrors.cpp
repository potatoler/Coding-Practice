#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 998244353;
int n, p[MaxN], sum;

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

inline int QuickPower(int a, int b){
	int res = 1;
	while(b){
		if(b & 1) res = res * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return res % Mod;
}

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		p[i] = Read();
		p[i] = (100 + (100-p[i]) * sum % Mod) * QuickPower(p[i], Mod-2) % Mod;
		sum = (sum + p[i]) % Mod;
	}
	printf("%lld", sum);
	return 0;
}