#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int Mod = 1e9 + 7;
typedef long long ll;
ll n;

inline ll QuickPow(ll a, ll b){
	ll tmp = a, ans = 1;
	while(b){
		if(b&1) ans = (ans % Mod * tmp % Mod) % Mod;
		tmp = tmp * tmp % Mod;
		b >>= 1;
	}
	return ans % Mod;
}

int main(){
	scanf("%lld",&n);
	printf("%lld\n", QuickPow(2, n-1) % Mod);
	return 0;
}