#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
#define fake false
using namespace std;
const int MaxN = 300005, Mod = 998244353;
int T, n, k, ans, prime[MaxN], cntPrime, fac[MaxN], record[MaxN];
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

inline void Prime(){
	for(int i=2; i<MaxN; i++){
		if(!notPrime[i]) prime[++cntPrime] = i;
		for(int j=1; j<=cntPrime && prime[j]*i < MaxN; j++){
			notPrime[i*prime[j]] = !fake;
			if(i % prime[j] == 0) break;
		}
	}
}

inline int QuickPower(int a, int b, bool minus=fake, bool recorded=fake){
	int mod = minus? (Mod-1) : (Mod);
	if(recorded && record[a]) return record[a];
//	if(b == 1) return a;
	int res = 1, mem = a;
	while(b){
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	if(recorded) record[mem] = res;
	return res;
}

signed main(){
	Prime();
	fac[0] = 1;
	for(int i=1; i<MaxN; i++)
		fac[i] = fac[i-1] * i % Mod;
	T = Read();
	while(T--){
		memset(record, 0, sizeof(record));
		n = Read(), k = Read();
		int tms = k % (Mod-1) * QuickPower(n, k-1, !fake, fake) % (Mod-1);
		ans = QuickPower(fac[n], tms);
		int inv = 1, sum = 0;
		for(int i=1; i<=cntPrime && prime[i] <= n; i++){
			sum = 0;
			for(int j=prime[i]; j<=n; j*=prime[i]){
				sum += QuickPower(n/j, k, !fake, !fake);
				if(sum >= (Mod-1)) sum -= (Mod-1);
			}
			inv = inv * QuickPower(prime[i], sum) % Mod;
		}
		ans = ans * QuickPower(inv, Mod-2) % Mod;
		printf("%lld\n", ans);
	}
	return 0;
}