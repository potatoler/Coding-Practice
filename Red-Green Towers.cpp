#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005, Mod = 1000000007;
int r, g, f[MaxN];

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
	r = Read(), g = Read();
	int h = sqrt(r*2 + g*2);
	while(h * (h+1) <= r*2+g*2)
		h++;
	f[0] = 1;
	for(int i=1; i<h; i++)	
		for(int j=r; j>=i; j--)
			f[j] = (f[j] + f[j-i]) % Mod;
	int ans = 0, sum = h * (h-1) / 2;
	for(int i=r; i>=0; i--){
		if(sum - i > g) break;
		ans = (ans + f[i]) % Mod;
	}
	printf("%lld", ans);
	return 0;
}