#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxM = 1000, Mod = 998244353;
int n, m, A, C[MaxM][MaxM];

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
	int res = 1;
	while(b){
		if(b&1) res = res * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return res;
}

signed main(){
	n = Read(), m = Read(), A = Read();
	C[0][0] = 1;
	for(int i=1; i<=max(m,n); i++){
		C[i][0] = 1;
		for(int j=1; j<=i; j++){
			C[i][j] = (C[i-1][j-1] + C[i-1][j]) % Mod;
		}
	}
	int ans = 0;
	for(int i=0; i<=n; i++){
		for(int j=1; j<=min(m,A); j++){
			int sum = 0;
			for(int k=1; k<=n-i; k++){
				sum = (sum + C[n-i][k] * QuickPower(A-j, n-i-k)) % Mod;
			}
			for(int k=1; k+i<=n && m-j*k>=i; k++){
				int tmp = 0;
				for(int l=0; l<=i && m-k*j-l*(j-1)>=i; l++){
					if(l & 1) tmp = (tmp - C[i][l] * C[m-k*j-l*(j-1)][i]) % Mod;
					else tmp = (tmp + C[i][l] * C[m-k*j-l*(j-1)][i]) % Mod; 
				}
				ans = (ans + tmp * C[n][i] % Mod * sum) % Mod;
				sum = (sum - C[n-i][k] * QuickPower(A-j, n-i-k)) % Mod;
			}
		}
	}
	ans = (ans * QuickPower(QuickPower(A,n), Mod-2) % Mod);
	printf("%lld", ans);
	return 0;
}