#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<map>
#define int long long
using namespace std;
const int MaxN = 5000006;
int n, m, a[MaxN], b[MaxN], p[MaxN];
int pre[MaxN], suf[MaxN];
int f[1003][1003];

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
	freopen("offa.in", "r", stdin);
	freopen("offa.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=n; i++)
		p[i] = Read();
	m = Read();
	int ptr = 1;
	bool flag = true;
	for(int i=1; i<=m; i++)
		b[i] = Read();
	for(int i=1; i<=m; i++){
		while(a[ptr] != b[i]){
			ptr++;
			if(ptr == n+1){
				flag = false;
				break;
			}
		}
		if(flag == false) break;
	}
	if(flag == false){
		printf("Impossible");
		return 0;
	}
	if(m == 1){
		for(int i=1; i<=n; i++)
			pre[i] = pre[i-1] + p[i];
		for(int i=n; i>=1; i--){
			suf[i] = suf[i+1];
			if(a[i] > b[1] || p[i] < 0) suf[i] += p[i];
		}
		int ans = LLONG_MAX;
		for(int i=1; i<=n; i++)
			if(a[i] == b[1]) ans = min(ans, pre[i-1]+suf[i+1]);	
		printf("%lld", ans);
		return 0;
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = f[0][1] = 0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(a[i] < b[j]) f[i][j] = f[i-1][j] +  min(0ll,p[i]);
			else if(a[i] > b[j]) f[i][j] = f[i-1][j] + p[i];
			else f[i][j] = min(f[i-1][j-1], min(f[i-1][j], f[i-1][j] + p[i]));
		}
	}
	printf("%lld", f[n][m]);
	return 0;
}