#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long 
using namespace std;
const int MAXN = 20, Mod = 2001000097;
int a, b, num[MAXN], dp[MAXN][MAXN][2][2];
//inline char fgc() {
//	static char buf[100000], *p1 = buf, *p2 = buf;
//	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) 
//		? EOF : *p1++;
//}

inline int Read(){
	int nums = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		nums = nums * 10 + ch - '0';
		ch = getchar();
	}
	return nums * op;
}

inline int DFS(int len, int cnt, int digit, bool lim, bool zero) {
	if(dp[len][cnt][lim][zero] != -1) return dp[len][cnt][lim][zero];
	if(!len) return dp[len][cnt][lim][zero] = cnt;
	int res = 0;
	for(int i = 0; i <= 9; i++) {
		if(lim && i > num[len]) break;
		res += DFS(len - 1, cnt + ((!zero || i) && i == digit), digit, 
			lim && i == num[len], zero && i == 0);
	}
	return dp[len][cnt][lim][zero] = res;
}

inline int work(int lim, int digit) {
	int len = 0;
	while(lim){
		num[++len] = lim % 10;
		lim /= 10;
	}
	memset(dp, -1, sizeof(dp));
	return DFS(len, 0, digit, true, true);
}

inline int Calculate(int l, int r){
	int res = 0;
	for(int i = 0; i <= 9; i++)
		res = res + (((work(r, i) % Mod - work(l - 1, i) % Mod + Mod) % Mod) * i) % Mod;
	return res;
}
signed main(){
	freopen("hash.ans", "r", stdin);
	freopen("hash.ans", "w", stdout);
	int T = Read();
	while(T--){
		int l = Read(), r = Read();
		int ans = 0;
		for(int i=l; i<=r; i++){
			ans = (ans + Calculate(i, r)) % Mod;
		}
//		ans = Calculate(l,r);
		printf("%lld\n", ans);
	}
	return 0;
}