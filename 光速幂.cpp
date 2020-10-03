#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 10000007;
int a, b, p, bl, bl1[MaxN], bl2[MaxN];

inline void Init(){
	bl1[0] = bl2[0] = 1 % p;
	for(int i=1; i<=bl; i++)
		bl1[i] = bl1[i-1] * a % p;
	for(int i=1; i<=bl; i++)
		bl2[i] = bl2[i-1] * bl1[bl] % p;
}

inline int Light_Speed_Power(int a, int b){
	return b<=bl ? bl1[b] : bl2[b/bl] * bl1[b-b/bl*bl] % p;
}

signed main(){
	cin>>a>>b>>p;
	bl = sqrt(b)+1;
	Init();
	cout<<a<<"^"<<b<<" mod "<<p<<"="<<Light_Speed_Power(a, b)<<endl;
	return 0;
}