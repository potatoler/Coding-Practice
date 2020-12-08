#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<climits>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005, Mod = 1000000007;
int n, f[MaxN][2];
vector<int> son[MaxN];

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
	n = Read();
	for(int i=2; i<=n; i++){
		int father = Read();
		son[father].push_back(i);
	}
	for(int x=n; x>=1; x--){
		f[x][1] = 1, f[x][0] = 0;
		int siz = son[x].size();
		if(!siz) continue;
		for(auto y : son[x]){
			int tmp1 = (f[x][0] * f[y][0] % Mod + f[x][1] * f[y][1] % Mod) % Mod,
			tmp2 = (f[x][1] * f[y][0] % Mod + f[x][0] * f[y][1] % Mod) % Mod;
			f[x][0] = (f[x][0] + tmp1) % Mod;
			f[x][1] = (f[x][1] + tmp2) % Mod;
		}
		f[x][0] = (f[x][0] * 2) % Mod;
		f[x][1] = (f[x][1] * 2) % Mod;
		int sum[3] = {1,1,0}, tmp = 0;
		for(auto y : son[x]){
			sum[0] = (sum[0] + (sum[0] * f[y][0] % Mod)) % Mod;
			tmp = sum[1];
			sum[1] = (sum[1] + (sum[2] * f[y][1] % Mod)) % Mod;
			sum[2] = (sum[2] + (tmp * f[y][1] % Mod)) % Mod;
		}
		f[x][1] = (f[x][1] - sum[0] + Mod) % Mod;
		f[x][0] = (f[x][0] - sum[2] + Mod) % Mod;
	}
	printf("%lld", (f[1][0] + f[1][1]) % Mod);
	return 0;
}