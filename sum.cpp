#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1000010, Mod = 998244353;
int n, k, a[MaxN], ans, predecessor[MaxN], successor[MaxN], serial[MaxN];

inline int read(){
	char x;
	int num;
	while(x=getchar(),x<'0'||x>'9');
	num=x-'0';
	while(x=getchar(),x>='0'&&x<='9') num*=10,num+=x-'0';
	return num;
}

inline bool cmp(int i, int j){
	return a[i] < a[j];
}

inline void Calculate(){
	for(int i=1;i<=n;i++){
		predecessor[i] = i-1;
		successor[i] = i+1;
	}
	for(int i=1;i<=n;i++){
		int x = serial[i], length = 1;
		int l = x, r = x;
		for(1; length < k; length++){
			if(predecessor[l]) l = predecessor[l];
			else break;
		}
		for(1; length < k; length++){
			if(successor[r] != n+1) r = successor[r];
			else break;
		}
		if(length == k){
			while(l <= x){
				if(r == n+1) break;
				ans = (ans + a[x] * (successor[r] - r) % Mod * (l - predecessor[l]) % Mod) % Mod;
				l = successor[l]; r = successor[r];
			}
		}
		predecessor[successor[x]] = predecessor[x];
		successor[predecessor[x]] = successor[x];
	}
}

signed main(){
	n = read();
	k = read();
	for(int i=1;i<=n;i++){
		a[i] = read();
		serial[i] = i;
	}
	sort(serial+1, serial+1+n, cmp);
	Calculate();
	reverse(serial+1, serial+1+n);
	Calculate();
	printf("%lld", ans);
	return 0;
}