#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MaxN=100005, Mod=999911659;
ll n,g;
ll factorial_of[MaxN], inverseofFctorial_of[MaxN];
inline ll QuickPow(ll baseNumber,ll powerTimes){
	ll answer;
	while(powerTimes){
		if(powerTimes & 1) answer = answer * baseNumber % Mod;
		baseNumber = baseNumber * baseNumber % Mod;
		powerTimes >>= 1;
	}
	return answer % Mod;
}
inline void Init(ll originalNumber){
	factorial_of[0] = 1;
	for(int i=1;i<originalNumber;i++)
		factorial_of[i] = factorial_of[i-1] * i % p;
	inverseofFctorial_of[originalNumber] = 0;
	inverseofFctorial_of[originalNumber - 1] = QuickPow(factorial_of[p-1], originalNumber - 2);
	for(int i=originalNumber-2;i>=0;i--)
		inverseofFctorial_of[i] = inverseofFctorial_of[i+1] * (i+1) % Mod;
}
inline ll CombinatorialNumber()