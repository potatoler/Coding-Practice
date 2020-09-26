#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<bitset>
using namespace std;
const int MaxN = 300000008, MaxP = 20000007;
int l, r, prime[MaxP], cntPrime, ans;
bitset <MaxN> notPrime;

inline void Euler(int l, int r){
	notPrime[0] = notPrime[1] = 1;
	for(int i=2; i<=r; i++){
		if(!notPrime[i]) prime[++cntPrime] = i;
		for(int j=1; j<=cntPrime && i*prime[j]<=r; j++){
			notPrime[i*prime[j]] = 1;
			if(i%prime[j] == 0) break;
		}
	}
}

int main(){
	scanf("%d%d", &l, &r);
	Euler(l, r);
	for(int i=5; i<=r; i+=4)
		if(i>=l && notPrime[i] == 0) ans++;
	if(l<=2 && r>=2) ans += 1;
	printf("%d", ans);
	return 0;
}