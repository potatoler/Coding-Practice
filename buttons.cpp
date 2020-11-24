#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
int n, m;

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

inline int Calculate(int x, int y){
	int res = 0;
	if(y<=x) return (x-y);
	else if(y&1) return res += 1 + Calculate(x,y+1);
	else return res += 1 + Calculate(x, y/2);
}

signed main(){
	n = Read(), m = Read();
	int ans = Calculate(n, m);
	printf("%lld", ans);
	return 0;
}