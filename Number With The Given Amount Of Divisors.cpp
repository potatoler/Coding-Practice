#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003, prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
int n, ans = LLONG_MAX;

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

inline void DFS(int now, int cur, int p, int cnt){
	if(cnt > n || now <= 0 || now > ans || cur > 15) return;
	if(cnt == n){
		ans = now;
		return;
	}
	for(int i=1;i<=p;++i) {
		DFS(now *= prime[cur], cur+1, i, cnt*(i+1));
	}
}
signed main(){
	n = Read();
	DFS(1,0,64,1);
	printf("%lld", ans);
	return  0;
}