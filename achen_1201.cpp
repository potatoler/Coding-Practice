#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006, Mod = 998244353;
int T, n, A, B, f[MaxN];

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

inline void DP(){
	f[0] = 1;
	for(int i=0; i<=1000000; i++){
		f[i] %= Mod;
		f[i+1] += f[i];
		f[i+3] += f[i];
	}
	return;
}

signed main(){
//	freopen("achen.in", "r", stdin);
//	freopen("achen.out", "w", stdout);
	DP();
	T = Read();
	while(T--){
		n = Read(), A = Read(), B = Read();
		if(A > B) swap(A,B);
		if(A > 1) A++;
		if(B < n) B--;
		if(B < A) printf("0\n");
		else printf("%lld\n", f[B-A]);
	}
	return 0;
}