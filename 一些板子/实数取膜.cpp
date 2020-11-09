#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int Mod = 19260817;
int a, b, x, y;

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = (num * 10 + ch - '0') % Mod;
		ch = getchar();
	}
	return num * op;
}

inline void ExGCD(int x, int y, int &a, int &b){
	if(!y){
		a = 1;
		b = 0;
		return;
	}
	ExGCD(y, x%y, a, b);
	int k = a;
	a = b;
	b = k - (x / y) * b;
	return;
}

signed main(){
	x = Read(), y = Read();
	if(y == 0){
		printf("Angry!");
		return 0;
	}
	int a = 0, b = 0;
	ExGCD(y, Mod, a, b);
	y = (a + Mod) % Mod;
	printf("%lld", (x%Mod*y%Mod)%Mod);
	return 0;
}