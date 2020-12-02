#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, a[MaxN], last[MaxN], len[MaxN], ans[MaxN];

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

inline bool cmp(int x, int y){
	if(len[x] == len[y]) return x < y;
	return len[x] < len[y];
}

signed main(){
//	freopen("number.in", "r", stdin);
//	freopen("number.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		len[a[i]] = max(len[a[i]], i-last[a[i]]);
		last[a[i]] = i;
	}
	for(int i=1; i<=n; i++)
		len[a[i]] = max(len[a[i]], n+1-last[a[i]]);
	sort(a+1, a+1+n, cmp);
//	for(int i=1; i<=n; i++)
//		printf("%lld %lld\n", a[i], len[a[i]]);
	int p = 1, cur = 0;
	for(int i=1; i<=n; i++){
		while(p<=n){
			if(len[a[p]] > i) break;
			else if(len[a[p]] <= i && a[p] > cur) cur = a[p];
			p++;
		}
		ans[i] = cur;
	}
	for(int i=1; i<=n; i++)
		printf("%lld ", ans[i]);
	return 0;
}