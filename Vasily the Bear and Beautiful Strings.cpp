#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 1000000007;
int n, m, g, fac[MaxN], ans;

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

inline int QuickPower(int a, int b, int p){
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}

inline void Init(){
	fac[0]=1;
	for(int i=1; i<MaxN; i++) 
		fac[i] = fac[i-1] * i % Mod;  
}

inline int C(int n, int m){
	return fac[n] * QuickPower(fac[m] * fac[n-m] % Mod, Mod-2, Mod) % Mod;
}

signed main(){
	n = Read(), m = Read(), g = Read();
	if(!n){
		if(g){
			if(m==1) printf("1");
			else printf("0");
		}
		else{
			if(m==1) printf("0");
			else printf("1");
		}
	}
	else if(!m){
		if(g){
			if(n&1) printf("0");
			else printf("1");
		}
		else{
			if(n&1) printf("1");
			else printf("0");
		}
	}
	else{
		Init();
		for(int i=0; i<=n; i+=2) 
			ans = (ans + C(n+m-1-i,m-1)) % Mod;
		if(m==1) 
			ans = (ans + (n&1 ? 1 : -1) + Mod) % Mod;
		if(g) 
			ans = (C(n+m,n) - ans + Mod) % Mod;
		printf("%lld",ans); 
	}
	return 0;
}