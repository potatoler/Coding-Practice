#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 1003, Mod = 1000000007;
int n, m, ans, one[MaxN], ome[MaxN], sun[MaxN], sum[MaxN];
int bin[MaxN], bim[MaxN], len, lem;

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

signed main(){
	n = Read(), m = Read();
	int tmp = n;
	while(tmp > 0){
		bin[++len] = tmp & 1;
		tmp >>= 1;
	}
	tmp = m;
	while(tmp > 0){
		bim[++lem] = tmp & 1;
		tmp >>= 1;
	}
	sun[0] = 1;
	for(int i=1; i<=len; i++){
		if(!bin[i]) sun[i] = sun[i-1];
		else sun[i] = ((1ll<<(i-1)) % Mod + sun[i-1]) % Mod;
//		printf("%lld ", sun[i]);
	}
//	printf("\n");
	sum[0] = 1;
	for(int i=1; i<=lem; i++){
		if(!bim[i]) sum[i] = sum[i-1];
		else sum[i] = ((1ll<<(i-1)) % Mod + sum[i-1]) % Mod;
//		printf("%lld ", sum[i]);
	}
//	printf("\n");
	for(int i=1; i<=len; i++){
		if(bin[i]){
			tmp = (n>>i) % Mod;
			one[i] = (tmp * ((1ll<<(i-1)) % Mod) % Mod + sun[i-1]) % Mod;
		}
		else{
			tmp = (((n>>(i-1)) - 1) >> 1) % Mod;
			one[i] = ((tmp+1) * ((1ll<<(i-1)) % Mod) % Mod);
		}
//		printf("%lld ", one[i]);
	}
//	printf("\n");
	for(int i=1; i<=lem; i++){
		if(bim[i]){
			tmp = (m>>i) % Mod;
			ome[i] = (tmp * ((1ll<<(i-1)) % Mod) % Mod + sum[i-1]) % Mod;
		}
		else{
			tmp = (((m>>(i-1)) - 1) >> 1) % Mod;
			ome[i] = ((tmp+1) * ((1ll<<(i-1)) % Mod) % Mod);
		}
//		printf("%lld ", ome[i]);
	}
	for(int i=1; i<=max(len,lem); i++)
		ans = (ans + ((n+1) % Mod * ome[i] % Mod - one[i] * ome[i] % Mod + (m+1) % Mod * one[i] % Mod) % Mod * ((1ll<<(i-1)) % Mod) % Mod) % Mod;
	printf("%lld", ans);
	return 0;
}