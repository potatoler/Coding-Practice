#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<set>
#define int long long
using namespace std;
int n, m, s[40], ans;
set<int> pre, suf;

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

inline void DFS(int l, int r, int sum){
	if(l == r){
		if(r == n) suf.insert(sum);
		else pre.insert(sum);
		return;
	}
	DFS(l+1, r, sum);
	DFS(l+1, r, (sum+s[l]) % m);
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=0; i<n; i++)
		s[i] = Read();
	DFS(0, n/2, 0);
	pre.insert(0);
	DFS(n/2, n, 0);
	suf.insert(0);
	set<int>::iterator it;
	for(it = pre.begin(); it!=pre.end(); it++){
		int cur = m - *it - 1;
		ans = max(ans, *(--suf.upper_bound(cur)) + *it);
	}
	printf("%lld", ans);
	return 0;
}