#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
//#define int long long
using namespace std;
const int MaxN = 1000006;
int n, k, a[MaxN], trie[MaxN*35][2], size[MaxN*35], cnt=1;
long long ans;

inline void Insert(int x){
	int p = 1;
	for(int i=30; ~i; i--){
		int digit = (x>>i) & 1;
		if(!trie[p][digit]) trie[p][digit] = ++cnt;
		p = trie[p][digit];
		size[p]++;
	}
	return;
}

inline int Query(int x){
	int p = 1, res = 0;
	for(int i=30; ~i; i--){
		int digit = (x>>i) & 1;
		if((k>>i) & 1) p = trie[p][!digit];
		else{
			res += size[trie[p][!digit]];
			p = trie[p][digit];
		}
	}
	res += size[p];
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
//	freopen("xor.in", "r", stdin);
//	freopen("xor.out", "w", stdout);
	n = Read(), k = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		a[i]^=a[i-1];
	}
	for(int i=1; i<=n; i++){
		Insert(a[i-1]);
		ans += Query(a[i]);
	}
	printf("%lld\n", ans);
	return 0;
}