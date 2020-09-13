#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 5000006, Mod = 998244353;
int f[MaxN], g[MaxN], p[MaxN];

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
	int ans = 1;
	while(y){
		if(y & 1) ans = ans * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return ans;
}

signed main(){
	int n = 5000000;
	for(int i=1; i<=n; i++)
		p[i+1] = (p[i] + i) % Mod;
	g[0] = 1;
	for(int i=1; i<=n; i++){
		g[i] = (f[i-1] + g[i-1]) * i % Mod;
		f[i] = (2*f[i-1] + g[i-1]) * p[i] % Mod;
	}
	for(int i=1; i<=n; i++)
		f[i] = (f[i] + g[i]) % Mod;
	p[0] = 1;
	for(int i=1; i<=n; i++)
		p[i] = i * p[i-1] % Mod;
	int x = Read(), T = Read();
	int a=0, b=0;
	for(int i=2; i*i<=x; i++){
		if(x % i == 0){
			x /= i;
			if(x % i == 0){
				x /= i;
				a++;
			}
			else b++;
		}
	}
	if(x != 1) b++;
	while(T--){
		n = Read();
		int ans = QuickPower(QuickPower(2,n-1), n-1) * QuickPower(f[n], a) % Mod * QuickPower(p[n], b) % Mod;
		printf("%lld\n", ans);
	}
	return 0;
}