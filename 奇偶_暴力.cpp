#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 200;
int t, n, m, s, sum = 0, ans, mx = 0;
int a[MaxN];

inline void DFS(int cnt){
	if(cnt == m+1){
		if(sum == s) ans ^= 1;
		return;
	}
	for(int i=1; i<=n; i++){
		sum += a[i];
		if(cnt < m && sum > s){
			sum -= a[i];
			continue;
		}
		if(cnt < m && sum + mx*(m-cnt) < s){
			sum -= a[i];
			continue;
		}
		DFS(cnt+1);
		sum -= a[i];
	}
	return;
}

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
	t = Read();
	while(t--){
		m = Read(), s = Read(), n = Read();
		sum = 0, mx = 0;
		for(int i=1; i<=n; i++)
			a[i] = Read(), mx = max(a[i], mx);
		DFS(1);
		printf("%lld", ans);
	}
	return 0;
}