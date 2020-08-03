#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 1e7 + 5;
int T, p, phi[MaxN], prime[MaxN];
bool notPrime[MaxN];

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

inline void Eular(int n){
	phi[1] = 1;
	for(int i=2;i<=n;i++){
		if(!notPrime[i]){
			prime[++prime[0]] = i;
			phi[i] = i-1;
		}
		for(int j=1; j <= prime[0] && i*prime[j] <= n; j++){
			notPrime[i*prime[j]] = true;
			if(i % prime[j] == 0){
				phi[i*prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i*prime[j]] = phi[i] * phi[prime[j]];
		}
	}
}

inline int QuickPower(int x, int b, int p){
	int res = 1;
	while(b){
		if(b & 1) res = res * x % p;
		x = x * x % p;
		b >>= 1;
	}
	return res;
}

inline int Solve(int p){
	if(p == 1) return 0;
	return QuickPower(2, Solve(phi[p]) + phi[p], p);
}

signed main(){
	T = Read();
	Eular(MaxN);
	while(T--){
		p = Read();
		printf("%lld\n", Solve(p));
	}
	return 0;
}