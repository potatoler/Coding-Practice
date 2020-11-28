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
const int Base = 131, Over = 998244353;
int n, f[MaxN][2], hsh[MaxN];
char str[15];

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

inline int HSH(char s[]){
	int len = strlen(s), res = 0;
	for(int i=0; i<len; i++)
		res = (res * Base + str[i]) % Over;
	return res;
}

signed main(){
	freopen("foot.in", "r", stdin);
	freopen("foot.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++){
		scanf("%s", str);
		hsh[i] = HSH(str);
	}
	f[1][0] = 1, f[1][1] = 0;
	f[2][0] = 1, f[2][1] = hsh[2] == hsh[1]? 0 : 1;
	for(int i=3; i<=n; i++){
		f[i][0] = (f[i-1][0] + f[i-1][1]) % Mod;
		f[i][1] = hsh[i] == hsh[i-1] ? 0 : ((f[i-2][0] + f[i-2][1]) % Mod);
	}
	int ans = (f[n][0] + f[n][1]) % Mod;
	printf("%lld", ans);
	return 0;
}