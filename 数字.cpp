#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxMul = 2520;
int digit[20], facor[MaxMul+1], cntFactor, f[20][MaxMul+1][50];

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

inline int GCD(int x, int y){
	return y == 0? x : GCD(y, x%y);
}

inline int DP(int length, int last, int mod, bool limited){
	if(!length) return (last % mod == 0);
	if(!limited && f[length][last][facor[mod]] != -1) return f[length][last][facor[mod]];
	int ans = 0, bound = limited? digit[length] : 9;
	for(int i=0; i<=bound; i++){
		int nextMod = i==0? mod : mod*i/GCD(mod, i);
		ans += DP(length-1, (last*10+i) % MaxMul, nextMod, limited&&i==bound);
	}
	if(!limited) f[length][last][facor[mod]] = ans;
	return ans;
}

inline int Calculate(int x){
	int len = 0;
	while(x){
		digit[++len] = x % 10;
		x /= 10;
	}
	return DP(len, 0, 1, 1);
}

signed main(){
	memset(f, -1, sizeof(f));
	for(int i=1; i<=MaxMul; i++)
		if(MaxMul % i == 0) facor[i] = ++cntFactor;
	int T = Read();
	while(T--){
		int l = Read(), r = Read();
		printf("%lld\n", Calculate(r) - Calculate(l-1));
	} 
	return 0;
}