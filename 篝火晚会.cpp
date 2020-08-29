#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 500005;
int ans, x[MaxN], y[MaxN], n, s[MaxN], a[MaxN], b[MaxN], l1, l2;

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
	n = Read();
	for(int i=1; i<=n; i++)
		x[i] = Read(), y[i] = Read();
	s[1] = 1, s[n] = x[1], s[2] = y[1];
	for(int i=3; i<=n-1; i++)
		if(x[s[i-1]] == s[i-2]) s[i] = y[s[i-1]];
		else s[i]=x[s[i-1]];
	for(int i=1; i<=n; i++){
		l1 = i-1;
		l2 = i+1;
		if(l1 < 1) l1 = n;
		if(l2 > n) l2 = 1;
		if((s[l1]!=x[s[i]] || s[l2]!=y[s[i]]) && (s[l2]!=x[s[i]] || s[l1]!=y[s[i]])){
			printf("-1");
			return 0;
		}
	}
	for(int i=1; i<=n; i++){
		a[(s[i]-i+n) % n]++;
		b[(s[i]+i-1) % n]++;
	}
	for(int i=0; i<=n-1; i++){
		if(ans<a[i]) ans = a[i];
		if(ans<b[i]) ans = b[i];
	}
	printf("%lld", n-ans);
	return 0;
}