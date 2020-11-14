#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 2500;
int g[MaxN][MaxN], t[MaxN][MaxN];

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
//	freopen("speech.in", "r", stdin);
//	freopen("speech.out", "w", stdout);
	int n = Read(), d = Read();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			g[i][j] = Read();
	int cur = 1, nxt = 2, stamp = 0, turn = 0, start = 0, last = 0;
	while(true){
		stamp++;
//		printf("%lld %lld\n", cur, nxt);
		t[nxt][cur] = stamp;
		last = cur;
		cur = nxt;
		nxt = g[cur][last];
		if(stamp == d){
			printf("%lld", last);
//			printf("\nNo circle!");
			return 0;
		}
		if(t[nxt][cur]){
			start = t[nxt][cur] - 1;
			turn = stamp - start;
			break;
		}	
	}
	d -= start;
	d %= turn;
	while(d--){
		last = cur;
		cur = nxt;
		nxt = g[cur][last];
	}
	printf("%lld", last);
	return 0;
}