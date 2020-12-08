#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 20000007;
char a[MaxN], b[MaxN];
int z[MaxN], p[MaxN];

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

inline void Z(char *str, char *cmp, int *res, int opt){
	int len = strlen(str+1), clen = strlen(cmp+1);
//	for(int i=1, j=1; i<=len && j<=clen; i++, j++)
//		if(str[i] == cmp[j]) res[1]++;
	if(opt == 2) z[1] = len;
	int l = 0, r = 0;
	for(int i=opt; i<=len; i++){
		if(i<=r) res[i] = min(r-i+1, z[i-l+1]);
		while(i+res[i] <= len && cmp[res[i]+1] == str[i+res[i]]) res[i]++;
		if(i+res[i]-1 > r){
			l = i;
			r = i+res[i]-1;
		}
	}
	return;
}

inline int Calculate(int *x, int l, int r){
	int res = 0;
	for(int i=l, pos=1; i<=r; i++, pos++)
		res = res ^ (pos * (x[i]+1));
	return res;
}

signed main(){
//	freopen("z.in", "r", stdin);
//	freopen("z.out", "w", stdout);
	scanf("%s%s", a+1, b+1);
	Z(b,b,z,2);
	Z(a,b,p,1);
//	for(int i=1; i<=strlen(b+1); i++)
//		printf("%lld ", z[i]);
//	for(int i=1; i<=strlen(a+1); i++)
//		printf("%lld ", p[i]);
	int zans = Calculate(z, 1, strlen(b+1));
	int pans = Calculate(p, 1, strlen(a+1));
	printf("%lld\n%lld", zans, pans);
	return 0;
}