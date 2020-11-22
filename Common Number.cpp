#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
int n, k;

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

inline int Calculate(int x){
	int res = 0, tmp = 1;
	while(x <= n){
		res += min(tmp, n-x+1);
		x<<=1;
		tmp<<=1;
	}
	return res;
}

signed main(){
	n = Read(), k = Read();
	int ans = -1;
	int l = 1, r = n/2, res = -1;
	while(l<=r){
		int mid = (l+r) >> 1;
		if(Calculate(mid*2) + Calculate(mid*2+1) >= k){
			res = mid*2;
			l = mid+1;
		}
		else r = mid-1;
	}
	ans = max(ans, res);
	l = 1, r = (n+1)/2, res = -1;
	while(l<=r){
		int mid = (l+r) >> 1;
		if(Calculate(mid*2-1) >= k){
			res = mid*2-1;
			l = mid+1;
		}
		else r = mid-1;
	}
	ans = max(ans, res);
	printf("%lld", ans);
	return 0;
}