#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
int n, ai[11], Mi[11], mi[11], mul = 1, X;
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

inline void ExGCD(int a, int b, int &x, int &y){
	if(b == 0){
		x = 1; y = 0;
		return;
	}
	ExGCD(b, a%b, x, y);
	int z = x;
	x = y; y = z - y * (a/b);
}

signed main(){
	n = Read();
	for(int i=1;i<=n;i++){
		mi[i] = Read();
		mul *= mi[i];
		ai[i] = Read();
	}
	for(int i=1;i<=n;i++){
		Mi[i] = mul / mi[i];
		int x = 0, y = 0;
		ExGCD(Mi[i], mi[i], x, y);
		X += ai[i] * Mi[i] * (x<0? x+mi[i] : x);
	}
	printf("%lld", X % mul);
	return 0;
}