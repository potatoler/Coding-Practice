#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 10004, Base = 131, Mod = 998244353;
int n, hsh[MaxN];
char s[MaxN];

inline int HSH(char str[]){
	int len = strlen(str);
	int res = 0;
	for(int i=0; i<len; i++)
		res = (res * Base + str[i]) % Mod;
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
	n = Read();
	for(int i=1; i<=n; i++){
		scanf("%s", s);
		hsh[i] = HSH(s);
	}
	int ans = 1;
	sort(hsh+1, hsh+1+n);
	for(int i=1; i<n; i++){
//		printf("%lld\n", hsh[i]);
		if(hsh[i] != hsh[i+1]) ans++;
	}
	printf("%lld", ans);
	return 0;
}