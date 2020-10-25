#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<utility>
#include<vector>
#define int long long
using namespace std;
int a[10][2];

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
//	freopen("coin.in", "r", stdin);
//	freopen("coin.out", "w", stdout);
	int T = Read();
	while(T--){
		int n = Read(), s = Read();
		if(s == 1) printf("%lld\n", (n+1)/2);
		if(s == 0){
			if(n & 1) printf("%lld\n", (n-1)/2);
			else{
				int k = 2;
				while(k <= n){
					k <<= 1;
				}
				k /= 2;
				printf("%lld\n", (n-k)/2);
			}
		}
	}
	return 0;
}