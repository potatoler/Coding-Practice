#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<set>
#define int long long
#define double long double
using namespace std;
int n, p;
int stack[1000], top;
double r;

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
	scanf("%lld%Lf%lld", &n, &r, &p);
	double tmp = (3.0 + 2.0 * sqrt(2));
	n -= 1;
	double res = 1.0;
	while(n){
		if(n & 1) res = res * tmp;
		tmp = tmp * tmp;
		n >>= 1;
	}
	int ans = res * r;
	while(p--){
//		printf("%lld", ans % 10);
		stack[++top] = ans % 10;
		ans /= 10;
		if(!ans) break;
	}
	while(top)
		printf("%lld", stack[top--]);
	return 0;
}