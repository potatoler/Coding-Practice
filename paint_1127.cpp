#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, T, prime[MaxN], cnt;
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

inline void Euler(){
	for(int i=2; i<MaxN; i++){
		if(!notPrime[i]) prime[++cnt] = i;
		for(int j=1; j<=cnt && i*prime[j]<MaxN; j++){
			notPrime[i*prime[j]] = true;
		}
	}
}

signed main(){
	Euler();
	T = Read();
	while(T--){
		n = Read();
		int tmp = n, ans = 0, tot = 0;
		bool flag = true;
		for(int i=2; i*i<=n; i++){
			if(n % i == 0){
				flag = false;
				break;
			}
		}
		if(flag){
			printf("%lld\n", n);
			continue;
		}
		for(int i=1; i<=cnt && prime[i] <= tmp; i++){
			if(tmp % prime[i] == 0){
				tot++, ans = prime[i];
				while(tmp % prime[i] == 0) tmp /= prime[i];
			}
		}
		if(tot == 1) printf("%lld\n", ans);
		else printf("1\n");
	}
	return 0;
}