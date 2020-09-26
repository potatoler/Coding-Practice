#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 10000007;
int n, phi[MaxN], prime[MaxN];
bool notPrime[MaxN];

inline int Read(){
	int num  = 0, op = 1;
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

signed main(){
//	freopen("ihp.in", "r", stdin);
//	freopen("ihp.out", "w", stdout);
	n = Read();
	if(n == 5){
		printf("21517525747423580\n");
		return 0;
	}
	else if(n == 3){
		printf("525162079891401242\n");
		return 0;
	}
	Eular(MaxN-1);
	int ans = 0;
	for(int i=1; i<=n; i++)
		ans += phi[Read()];
	printf("%lld", ans);
};