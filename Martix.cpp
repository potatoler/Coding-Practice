#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100005;
const long long Mod = 1e9+7;
int n;
long long a, b;
long long l[MaxN], t[MaxN];
long long factorial[MaxN*2], inverse[MaxN*2];

inline long long QuickPower(long long x, long long p){
	long long ans = 1;
	while(p){
		if(p & 1) ans = ans * x % Mod;
		x = x * x % Mod;
		p >>= 1;
	}
	return ans;
}

inline void Factorial(){
	factorial[0] = inverse[0] = 1;
	for(int i=1;i<=MaxN*2;i++){
		factorial[i] = factorial[i-1] * i % Mod;
		inverse[i] = QuickPower(factorial[i], Mod-2);
	}
}

inline long long C(long long m, long long n){
	return factorial[n] * inverse[n-m] % Mod * inverse[m] % Mod;
}

int main(){
	scanf("%d%lld%lld",&n,&a,&b);
	for(int i=1;i<=n;i++)
		scanf("%lld",&l[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld",&t[i]);
	int answer = 0;
	Factorial();
	for(int i=2;i<=n;i++)
		answer = (answer + l[i] * QuickPower(a, n-1) % Mod * QuickPower(b, n-i) % Mod * C(n-2, n*2-i-2)) % Mod;
	for(int i=2;i<=n;i++)
		answer = (answer + t[i] * QuickPower(a, n-i) % Mod * QuickPower(b, n-1) % Mod * C(n-2, n*2-i-2)) % Mod;
	printf("%d",answer);
//	for(int i=1;i<=10;i++){
//		for(int j=1;j<=i;j++){
//			printf("%lld ",C(j,i));
//		}
//		printf("\n");
//	}
//	for(int i=1;i<=10;i++)
//		printf("%lld %lld\n",factorial[i],inverse[i]);
		
	return 0;
}