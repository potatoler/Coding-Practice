#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 10000007;
int n, ans, prime[MaxN], phi[MaxN], sum[MaxN];
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
	for(int i=2; i<=n; i++){
		if(!notPrime[i]){
			prime[++prime[0]] = i;
			phi[i] = i-1;
		}
		for(int j=1; j<=prime[0] && i*prime[j] <= n; j++){
			notPrime[i*prime[j]] = true;
			if(i % prime[j] == 0){
				phi[i*prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i*prime[j]] = phi[i] * phi[prime[j]];
		}
	}
	return;
}

signed main(){
	n = Read();
	Eular(n);
	for(int i=1; i<=n; i++)
		sum[i] = sum[i-1] + phi[i];
	for(int i=1; i<=prime[0] && prime[i] <= n; i++)
		ans += (sum[n/prime[i]] << 1) - 1;
	printf("%lld\n", ans);
//	for(int i=1; i<=n; i++)
//		printf("%lld ", phi[i]);
	return 0;
}