#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int digit = 20;
int dp[digit][11];
int l, r, x, y, num[digit];

inline int Read(){
	int nu = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		nu = nu * 10 + ch - '0';
		ch = getchar();
	}
	return nu * op;
}

inline int DFS(int dep, bool limit, int lst){
	if(dep == 0) return 1;
	if(!limit && dp[dep][lst] != -1) return dp[dep][lst];
	int up = limit ? num[dep] : 9;
	int res = 0;
	for(int i=0; i<=up; i++){
	    if(lst == 10 && i == 0) res += DFS(dep-1, limit && i == up, 10);
		else{
			if(i == y && lst == x) continue;
			res += DFS(dep-1, limit && i==up, i);
		}
	}
	if(!limit) dp[dep][lst]=res;	
	return res;
}

inline int Solve(int a){
	int cnt=0;
	while(a){
		num[++cnt] = a % 10;
		a /= 10;
	}
	return DFS(cnt, true, 10);
}

signed main(){
	l = Read(), r = Read(), x = Read(), y = Read();
	memset(dp, -1, sizeof(dp));
	printf("%lld", (Solve(r) - Solve(l-1)));
}
