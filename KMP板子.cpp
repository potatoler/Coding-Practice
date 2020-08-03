#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
const int MaxN = 1000010;
char a[MaxN], b[MaxN];
int alen, blen, nxt[MaxN], p;

signed main(){
	scanf("%s%s", a+1, b+1);
	alen = strlen(a+1);
	blen = strlen(b+1);
	for(int i=2;i<=blen;i++){
		while(p && b[i] != b[p+1])
			p = nxt[p];
		if(b[p+1] == b[i]) p++;
		nxt[i] = p;
	}
	p = 0;
	for(int i=1;i<=alen;i++){
		while(p > 0 && b[p+1] != a[i])
			p = nxt[p];
		if(b[p+1] == a[i]) p++;
		if(p == blen){
			printf("%lld\n", i-blen+1);
			p = nxt[p];
		}
	}
	for(int i=1;i<=blen;i++)
		printf("%lld ",nxt[i]);
}