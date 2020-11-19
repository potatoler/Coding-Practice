#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#define int long long
using namespace std;
int T;

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
	T = Read();
	while(T--){
		int a = Read(), b = Read(), c = Read();
		int f = c*a, cost = 0, plus = 0;
		while(c){
			f = min(f, (c-plus) * a + cost);
			plus = 0;
			if((c&3) == 3){
				c++;
				plus = 1;
				cost += a;
			}
			else if((c&1) == 1){
				c--;
				cost += a;
			}
			cost += b;
			c >>= 1;
		}
		printf("%lld\n", f);
	}
	return 0;
}