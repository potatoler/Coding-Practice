#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<utility>
#include<cctype>
#include<map>
//#define int __int128
using namespace std;
__int128 k, m;
map<__int128,int> f;

inline __int128 Read(){
	__int128 num = 0, op = 1;
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

inline void Write(__int128 x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) Write(x/10);
	putchar(x % 10 + '0');
}

inline __int128 QuickPower(__int128 a, __int128 x, __int128 p){
	__int128 res = 1;
	while(x){
		if(x & 1) res = res * a % p;
		a = a * a % p;
		x >>= 1;
	}
	return res;
}

inline __int128 BSGS(__int128 a, __int128 b, __int128 p){ // The original BSGS algorithm
	f.clear();
	__int128 m = ceil(sqrt((double)p));
	b %= p;
	for(__int128 i=1;i<=m;i++){
		b = b * a % p;
		f[b] = i;
	}
	__int128 tmp = QuickPower(a, m, p);
	b = 1;
	for(__int128 i=1;i<=m;i++){
		b = b * tmp % p;
		if(f[b]) return (i * m - f[b] + p) % p;
	}
	return -1;
}

signed main(){
	k = Read(), m = Read();
	k = k * 9 + 1;
	__int128 ans = BSGS(10, k, m);
	Write(ans);
	return 0;
}