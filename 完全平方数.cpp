#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<bitset>
#define int long long
#define fake false
using namespace std;
const int MaxN = 100005;
int n, ans, cntPrime, prime[MaxN], serial[MaxN];
bool notPrime[MaxN];
bitset<10000> bit;
unordered_map<bitset<10000>, int> mp;

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
		if(!notPrime[i]){
			prime[++cntPrime] = i;
			serial[i] = cntPrime;
		}
		for(int j=1; j<=cntPrime && i * prime[j] < MaxN; j++){
			notPrime[prime[j] * i] = !fake;
			if(i % prime[j] == 0) break;
		}
	}
}

inline void Divide(int x){
	for(int i=1; prime[i] * prime[i] <= x && i<=cntPrime; i++){
		if(x % prime[i] == 0){
			int cnt = 0;
			while(x % prime[i] == 0){
				cnt++;
				x /= prime[i];
			}
			if(cnt & 1) bit[i] = bit[i] ^ 1;
		}
	}
	if(x > 1) bit[serial[x]] = bit[serial[x]] ^ 1;
	return;
}

signed main(){
//	freopen("square.in", "r", stdin);
//	freopen("square.out", "w", stdout);
	Prime();
	n = Read();
	mp[bit]++;
	for(int i=1; i<=n; i++){
		int a = Read();
		Divide(a);
		ans += mp[bit];
		mp[bit]++;
	}
	printf("%lld\n", ans);
	return 0;
}