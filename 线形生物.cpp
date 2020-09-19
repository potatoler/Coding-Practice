#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 1000006, Mod = 998244353;
int degree[MaxN], f[MaxN], sum[MaxN];
vector<int> to[MaxN];

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

inline int Get(int x){
	int ans = 0;
	for(int i=0; i<to[x].size(); i++){
		if(to[x][i] == x) ans = (ans + 1) % Mod;
		else ans = (ans + sum[x-1] - sum[to[x][i]-1] + 1 + Mod) % Mod;
	}
	return ans;
}

signed main(){
	int id = Read(), n = Read(), m = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		degree[u]++;
		to[u].push_back(v);
	}
	for(int i=1; i<=n; i++){
		f[i] = (Get(i) + 1) % Mod;
		sum[i] = (sum[i-1] + f[i]) % Mod;
	}
	printf("%lld", sum[n]);
	return 0;
}