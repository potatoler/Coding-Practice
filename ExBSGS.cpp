#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<map>
#define int long long
using namespace std;
int a, b, p;
map<int,int> f;

inline int GCD(int a, int b){
	if(!b) return a;
	return GCD(b, a%b);
}

inline void ExGCD(int a, int b, int &x, int &y){
	if(!b) x = 1, y = 0;
	else{
		ExGCD(b, a%b, x, y);
		int t = x;
		x = y, y = t-a/b * y;
	}
}

inline int Inv(int a, int b){
	int x, y;
	ExGCD(a, b, x, y);
	return (x % b + b) % b;
}

inline int QuickPower(int a, int x, int p){
	int res = 1;
	while(x){
		if(x & 1) res = res * a % p;
		a = a * a % p;
		x >>= 1;
	}
	return res;
}

inline int BSGS(int a, int b, int p){ // The original BSGS algorithm
	f.clear();
	int m = ceil(sqrt(p));
	b %= p;
	for(int i=1;i<=m;i++){
		b = b * a % p;
		f[b] = i;
	}
	int tmp = QuickPower(a, m, p);
	b = 1;
	for(int i=1;i<=m;i++){
		b = b * tmp % p;
		if(f[b]) return (i * m - f[b] + p) % p;
	}
	return -1;
}

inline int ExBSGS(int a, int b, int p){ // ExBSGS-Addon, based on the original algorithm, whith several times of transition. Do the original one when GCD(a,p) returns 1
	if(b == 1 || p == 1) return 0;
	int g = GCD(a, p), k = 0, na = 1;
	while(g > 1){
		if(b % g != 0) return -1;
		k++;
		b /= g;
		p /= g;
		na = na * (a / g) % p;
		if(na == b) return k;
		g = GCD(a, p);
	}
	int f = BSGS(a, b * Inv(na, p) % p, p);
	if(f == -1) return -1;
	return f + k;
}

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
	return num;
}

signed main(){
	a = Read(), p = Read(), b = Read();
	while(a || b || p){
		a %= p, b %= p;
		int t = ExBSGS(a, b, p);
		if(t == -1) printf("No Solution\n");
		else printf("%lld\n", t);
		a = Read(), p = Read(), b = Read();
	}
//	printf("%lld", GCD(a, p));
	return 0;
}