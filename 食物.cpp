#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int Mod = 10007, Inv = 1668;
int n;

inline int Read(){
	int num = 0, op = 1;
		char x = getchar();
		while(x < '0' || x > '9') {
			if(x == '-') op = -1;
			x = getchar();
		}
		while(x >= '0' && x <= '9') {
			num = (num * 10 + x - '0') % Mod;
			x = getchar();
		}
		return num * op;
}

signed main(){
	n = Read();
	int ans = ((n+2) % Mod * (n+1) % Mod * n % Mod * Inv % Mod);
	printf("%lld", ans);
	return 0;
}