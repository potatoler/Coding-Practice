#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
const int MaxN = 200000;
int n, phi[MaxN * 5];

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

inline void Init(){
	memset(phi, 0, sizeof(phi));
	phi[1] = 2;
	for(int i=2; i<=MaxN; i++){
		if(!phi[i]){
			for(int j=i; j<=MaxN; j+=i){
				if(!phi[j]) phi[j] = j;
				phi[j] = phi[j] / i * (i-1);
			}
		}
	}
}

inline int GCD(int a, int b){
	return b? GCD(b,a%b):a;
}

signed main(){
	Init();
	while(true){
		n = Read();
		if(!n) break;
		int ans = 0;
		for(int i=1; i<=MaxN; i++){
			if(ans + phi[i] >= n){
				for(int j=0; j<=i; j++){
					if(GCD(i,j) == 1) ans++;
					if(ans == n){
						printf("%lld/%lld\n", j, i);
						break;
					}
				}
				break;
			}
			ans += phi[i];
		}
	}
	return 0;
}