#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int Mod = 1000000007;
int n, m;

inline int QuickPower(int a, int b){
	int res = 1;
	while(b){
		if(b&1) res = res*a % Mod;
		a = a*a % Mod;
		b >>= 1;
	}
	return res;
}

signed main(){
	scanf("%lld%lld", &n, &m);
	if(n > m) swap(n,m);
	if(n == 1) printf("%lld", QuickPower(2,m) % Mod);
	else if(n == 2) printf("%lld", 4 * QuickPower(3,m-1) % Mod);
	else if(n == 3) printf("%lld", 112 * QuickPower(3,m-3) % Mod);
	else{
		if(m == n) printf("%lld", (83 * QuickPower(8,n) % Mod + 5 * QuickPower(2,n+7) % Mod) * 190104168 % Mod);
		else printf("%lld", (83 * QuickPower(8,n) % Mod + QuickPower(2,n+8) % Mod) * QuickPower(3,m-n-1) % Mod * 570312504 % Mod);
	}
	return 0;
}