#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int MaxN = 100005;
int n, m, ans, a[MaxN], pre[MaxN];

inline void Change(int x){
		return;
}

inline int Query(int l, int r){
	int res = 0;
	while(true){
		res = res | a[r];
		if(l == r) break;
		r--;
		while(r-l >= lowbit(r)){
			res = res | pre[r];
			r -= lowbit(r);
		}
	}
	return res;
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
//	freopen("evolve.in", "r", stdin);
//	freopen("evolve.my", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		pre[i] = a[i];
		for(int j=1; j<lowbit(i); j<<=1)
			pre[i] |= pre[i-j];
	}
	for(int i=1; i<n; i++){
		int l = i, r = n;
		while(l < r){
			int mid = (l+r+1) >> 1;
			if(Query(i, mid) < m) l = mid;
			else r = mid-1;
		}
		ans += l-i;
//		printf("%lld\n", l-i);
	}
	printf("%lld", ans);
	return 0;
}