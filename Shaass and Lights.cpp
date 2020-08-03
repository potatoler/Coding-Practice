#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1005, Mod = 1000000007;
int n, m, light[MaxN], length[MaxN], fac[MaxN], inv[MaxN], cntRange;

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
	return ans % Mod;
}

signed main(){
	n = Read(), m = Read();
	int ans = 1;
	for(int i=1;i<=m;i++)
		light[i] = Read();
	sort(light+1, light+1+m);
	length[++cntRange] = light[1] - 1;
	for(int i=2;i<=m;i++)
		if(light[i] - light[i-1] > 1) length[++cntRange] = light[i] - light[i-1] - 1;
	length[++cntRange] = n - light[m];
	for(int i=2;i<cntRange;i++)
		ans = (ans * QuickPower(2, length[i]-1)) % Mod;
	fac[0] = inv[0] = 1;
	for(int i=1;i<=n-m;i++)
		fac[i] = (fac[i-1] * i) % Mod;
	inv[n-m] = QuickPower(fac[n-m], Mod-2) % Mod;
	for(int i=n-m-1;i>=1;i--)
		inv[i] = (inv[i+1] * (i+1)) % Mod;
	ans = (ans * fac[n-m]) % Mod;
	for(int i=1;i<=cntRange;i++)
		ans = (ans * inv[length[i]]) % Mod;
	printf("%lld", ans);
	return 0;
}