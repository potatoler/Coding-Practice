#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
int a, b, c, d;

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

inline int GCD(int x, int y){
	if(!y) return x;
	return GCD(y, x%y);
}

signed main(){
//	freopen("a.in", "r", stdin);
//	freopen("a.out", "w", stdout);
	int T = Read();
	while(T--){
		a = Read(), b = Read(), c = Read(), d = Read();
		if(!a && !b && !c){
			if(!d) puts("YES");
			else puts("NO");
		}
		else{
			int gcd = GCD(GCD(a,b), c);
			if(d % gcd == 0) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}