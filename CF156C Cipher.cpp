#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 102, Mod = 1000000007;
int t, f[MaxN][MaxN*26], sum, length;
char str[MaxN];

inline int DP(int cur, int last){
	if(last < 0) return 0;
	if(!cur) return !last;
	if(f[cur][last] != -1) return f[cur][last];
	f[cur][last] = 0;
	for(int i=0; i<26; i++)
		f[cur][last] = (f[cur][last] + DP(cur-1, last-i)) % Mod;
	return f[cur][last];
}

signed main(){
	scanf("%lld", &t);
	memset(f, -1, sizeof(f));
	while(t--){
		sum = length = 0;
		scanf("%s", str+1);
		length = strlen(str+1);
		for(int i=1; i<=length; i++)
			sum += str[i] - 'a';
		printf("%lld\n", (DP(length, sum) + Mod - 1) % Mod);
	}
	return 0;
}