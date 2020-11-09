#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int fr[MaxN], to[MaxN], n, m, ans;

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
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		fr[i] = Read(), to[i] = Read();
		ans += abs(to[i] - fr[i]);
	}
	fr[n+1] = m, to[n+1] = 0;
	sort(fr+1, fr+1+n+1);
	sort(to+1, to+1+n+1);
	for(int i=1; i<=n+1; i++)
		ans += abs(fr[i] - to[i]);
	printf("%lld", ans);
	return 0;
}