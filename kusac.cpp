#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
int n, m;

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

inline int GCD(int a, int b){
	return b? GCD(b,a%b) : a;
}

signed main(){
	n = Read(), m = Read();
	int ans = m - 1 - (GCD(m,n) - 1);
	printf("%lld", ans);
	return 0;
}