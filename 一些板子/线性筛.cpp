#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100000008;
int n, q, prime[MaxN], cnt;
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
		for(int j = 1; j<=cnt && i*prime[j]<MaxN; j++){
			notPrime[i*prime[j]] = true;
		}
	}
	return;
}

signed main(){
	Euler();
	n = Read(), q = Read();
	while(q--){
		int k = Read();
		printf("%lld\n", prime[k]);
	}
	return 0;
}