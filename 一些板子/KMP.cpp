#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1000006;
char a[MaxN], b[MaxN];
int nxt[MaxN], alen, blen;

inline void GetNext(){
	int p1 = 0, p2;
	nxt[0] = p2 = -1;
	while(p1 < blen)
		if(p2 == -1 || b[p1] == b[p2]) nxt[++p1] = ++p2;
		else p2 = nxt[p2];
	return;
}

inline void KMP(){
	int p1 = 0, p2 = 0;
	while(p1 < alen){
		if(p2 == -1 || a[p1] == b[p2]){
			p1++;
			p2++;
		}
		else p2 = nxt[p2];
		
		if(p2 == blen){
			printf("%lld\n", p1-blen+1);
			p2 = nxt[p2];
		}
	}
	return;
}

signed main(){
	scanf("%s%s", a, b);
	alen = strlen(a), blen = strlen(b);
	GetNext();
	KMP();
	for(int i=1; i<=blen; i++)
		printf("%lld ", nxt[i]);
	return 0;
}