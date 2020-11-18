#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 5000006;
int n;

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

signed main(){
//	freopen("sequence.in", "r", stdin);
//	freopen("sequence.out", "w", stdout);
	while(true){
		n = Read();
		if(!n) break;
		int gcd = 1;
		while(n > 3){
			for(int i=1; i<=n-n/2; i++)
				printf("%lld ", gcd);
			n /= 2;
			gcd *= 2;
		}
		if(n == 3) printf("%lld %lld %lld\n", gcd, gcd, gcd*3);
		else if(n == 2) printf("%lld %lld\n", gcd, gcd*2);
		else printf("%lld\n", gcd);
	}
	return 0;
}