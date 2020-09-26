#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxX = 10000007, MaxN = 1000006, MaxM = 50004;
int n, m, a[MaxX], sum[MaxN], prime[MaxX], cntPrime;
bool notPrime[MaxX];

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

inline void Init(){
	prime[++cntPrime] = 2;
	int factor;
	for(int i=3; i<MaxX; i+=2){
		if(notPrime[i]) continue;
		prime[++cntPrime] = i;
		factor = i << 1;
		for(int j=i; j<MaxX; j+=factor)
			if(!notPrime[j]) notPrime[j] = true;
	}
}

signed main(){
	Init();
	n = Read();
	for(int i=1; i<=n; i++)
		a[Read()]++;
	for(int i=1; i<=cntPrime; i++){
		for(int j=prime[i]; j<MaxX; j += prime[i]){
			sum[i] += a[j];
		}
	}

	for(int i=1; i<=cntPrime; i++)
		sum[i] += sum[i-1];
	m = Read();
	for(int i=1; i<=m; i++){
		int x = Read(), y = Read();
		printf("%lld\n", sum[lower_bound(prime+1, prime+1+cntPrime, y+1) - prime - 1] - sum[lower_bound(prime+1, prime+1+cntPrime, x) - prime - 1]);
	}
	return 0;
}