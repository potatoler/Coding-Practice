#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a, b, cntten[20], ten[20], digit[20], cnta[20], cntb[20];

inline void Count(ll x, ll *cnt){
	memset(digit, 0, sizeof(digit));
	int len = 0;
	while(x){
		digit[++len] = x % 10;
		x = x / 10;
	}
	for(int i=len;i>=1;i--){
		for(int j=0;j<=9;j++)
			cnt[j] += cntten[i-1] * digit[i];
		for(int j=0;j<digit[i];j++)
			cnt[j] += ten[i-1];
		ll y = 0;
		for(int j=i-1;j>=1;j--)
			y = y * 10 + digit[j];
		cnt[digit[i]] += y + 1;
		cnt[0] -= ten[i-1];
	}
}

int main(){
	scanf("%lld%lld",&a,&b);
	ten[0] = 1;
	for(int i=1;i<20;i++){
		cntten[i] = cntten[i-1] * 10 + ten[i-1];
		ten[i] = 10 * ten[i-1];
	}
	Count(a-1, cnta); Count(b, cntb);
	for(int i=0;i<=9;i++)
		printf("%lld ", cntb[i] - cnta[i]);
	return 0;
}