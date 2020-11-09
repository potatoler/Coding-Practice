#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#include<queue>
#define int unsigned long long
using namespace std;
const int MaxN = 1000006;
int n, m, c, k, cnt, a[MaxN];
bool hv[100000008];
int ok, limited;

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
	freopen("zoo.in", "r", stdin);
	freopen("zoo.out", "w", stdout);
	n = Read(), m = Read(), c = Read(), k = Read();
	int animal = 0;
	for(int i=1; i<=n; i++)
		animal |= Read();
	for(int i=1; i<=m; i++){
		int p = Read(), q = Read();
		limited |= (1ull<<p);
		if(animal & (1ull<<p)) hv[q] = true;
		if(hv[q]) ok |= (1ull<<p);
	}
//	printf("%lld %lld", limited, ok);
	for(int i=0; i<k; i++)
		if((ok & (1ull<<i)) || !(limited & (1ull<<i))) cnt++;
	if(cnt <= 63) printf("%llu", (1ull<<cnt) - n);
	else{
		int ans = ((1ull<<63)-1) | (1ull<<63);
		if(!n) printf("18446744073709551616");
		else{
			n--;
			printf("%llu", ans - n);
		}
	}
	return 0;
}