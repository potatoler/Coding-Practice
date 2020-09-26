#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 1000000007;
int k, ans;
char a[MaxN];

inline int QuickPower(int a, int b){
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans;
}

signed main(){
	scanf("%s%lld", a, &k);
	int len = strlen(a);
	for(int i=0; i<len; i++)
		if(a[i] == '0' || a[i] == '5')
			(ans += QuickPower(2, i)) %= Mod;
	ans = ans * (QuickPower(2,len*k)-1) % Mod * QuickPower(QuickPower(2,len)-1, Mod-2) % Mod;
	printf("%lld", ans);
	return 0;
}