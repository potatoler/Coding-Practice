#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 200005;
int n, p, q;

struct Vertex{
	int x, y;
	double d;
	Vertex() = default;
	Vertex(int xx, int yy): x(xx), y(yy){
		d = ((double)q*y - (double)p*x) / (double)q;
	}
	bool operator < (const Vertex &a) const{
		return d < a.d;
	}
}vertex[MaxN];

struct Frac{
	int numerator, denominator;
	
	Frac ABS(){
		return Frac(abs(numerator),abs(denominator));
	}
	inline int GCD(int x, int y){
		return y == 0 ? x : GCD(y, x%y);
	}
	Frac(int nn = 0, int dd = 1): numerator(nn), denominator(dd){
		if(denominator < 0) numerator = -numerator, denominator = -denominator;
		int t = GCD(abs(numerator), denominator);
		numerator /= t;
		denominator /= t;
	}
	
	bool operator < (const Frac &a) const{
		return (double)numerator * a.denominator < (double)denominator * a.numerator;
	}
	bool operator == (const Frac &a) const{
		return numerator == a.numerator && denominator == a.denominator;
	}
	Frac operator - (const Frac &a) const{
		return Frac(numerator * a.denominator - denominator * a.numerator, denominator * a.denominator);
	}
};

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
	n = Read(), p = Read(), q = Read();
	for(int i=1; i<=n; i++){
		int x = Read(), y = Read();
		vertex[i] = Vertex(x,y);
	}
	sort(vertex+1, vertex+1+n);
	Frac ans(0,1), tmp(1,0), standard(p,q);
	for(int i=1; i<n; i++){
		Frac k = Frac(vertex[i+1].y - vertex[i].y, vertex[i+1].x - vertex[i].x);
		Frac deltak = (k - standard).ABS();
		if(deltak < tmp || (deltak == tmp && k < ans)){
			ans = k;
			tmp = deltak;
		}
	}
	printf("%lld/%lld", ans.numerator, ans.denominator);
}