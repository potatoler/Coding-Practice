#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 1000000007;
int n, m, fac[MaxN], inv[MaxN];
char s[MaxN];

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

inline int QuickPower(int a, int b){
	int ans = 1;
	while(b){
		if(b&1) ans = ans * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return ans;
}

inline void Init(){
	fac[0] = 1;
	for(int i=1; i<MaxN; i++)
		fac[i] = fac[i-1] * i % Mod;
	inv[MaxN-1] = QuickPower(fac[MaxN-1], Mod-2);
	for(int i=MaxN-2; i>=0; i--)
		inv[i] = inv[i+1] * (i+1) % Mod;
	return;
}

inline int C(int x, int y){
	return fac[x] * inv[y] % Mod * inv[x-y] % Mod;
}

inline int Cat(int n){
	return (C(2*n, n) - C(2*n, n-1) + Mod) % Mod;
}

signed main(){
	Init();
	n = Read(), m = Read();
	scanf("%s", s+1);
	int paired, needLeft, needRight;
	for(int i=1; i<=m; i++){
		if(s[i] == '(') needRight++;
		else{
			if(!needRight) needLeft++;
			else needRight--, paired++;
		}
	}
//	for(int i=1; i<=10; i++)
//		printf("%lld ", Cat(i));
	printf("%lld %lld %lld\n", needLeft, needRight, paired);
	int left = n - m - needRight - needLeft, pairedPlan = Cat(left/2);
	printf("%lld %lld\n", left, pairedPlan);
	int ans = 0;
	for(int i=0; i<=left/2; i++){
		for(int j=0; j<=(left-2*i)/2; j++){
			int leftPlan = C(needLeft+i, i), rightPlan = C(needRight+j, j);
			printf("%lld %lld %lld %lld\n", i, j, leftPlan, rightPlan);
			ans += leftPlan * rightPlan % Mod;
		}
	}
	ans = ans * pairedPlan % Mod;
	printf("%lld", ans);
	return 0;
}