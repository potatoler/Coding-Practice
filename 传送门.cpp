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
const int MaxN = 200005;
int n, a[MaxN], q[MaxN], below[MaxN][20], above[MaxN][20], idx[MaxN];
int stack[MaxN], top;
inline int GCD(int,int);
inline int Read();
class Fraction{
	public:
	int nume, deno;
	
	Fraction(int,int);
	
	inline bool operator <= (const Fraction &y) const{ return nume * y.deno <= y.nume * deno;}
	
	inline bool operator >= (const Fraction &y) const{ return nume * y.deno >= y.nume * deno;}
	
	inline bool operator == (const Fraction &y) const { return nume == y.nume && deno == y.deno;}
	
	inline bool operator !(){
		if(Fraction(nume,deno) == Fraction(INT_MAX, 1)) return true;
		else return false;
	}
	
	inline Fraction Reverse();
	
	inline void Print();
};
inline Fraction Cross(int,int);
inline bool cmp(int,int);
inline bool AboveOK(int,int);
inline bool BelowOK(int,int);

signed main(){
	n = Read();
	for(int i=1; i<=n; i++){
		a[i] = Read();
		idx[i] = i;
	}
	for(int i=1; i<=n; i++)
		q[i] = Read();
	sort(idx+1, idx+1+n, cmp);
	
	top = 0;
	for(int i=1; i<=n; i++){
		int j = idx[i];
		while((top && !Cross(j,stack[top])) || (top >= 2 && Cross(j,stack[top-1]) <= Cross(j,stack[top]))) top--;
		above[j][0] = stack[top];
		stack[++top] = j;
	}
	top = 0;
	for(int i=n; i>=1; i--){
		int j = idx[i];
		while((top && !Cross(j,stack[top])) || (top >= 2 && Cross(j,stack[top-1]) <= Cross(j,stack[top]))) top--;
		below[j][0] = stack[top];
		stack[++top] = j;
	}
	
	for(int k=1; k<=18; k++)
		for(int i=1; i<=n; i++)
			above[i][k] = above[above[i][k-1]][k-1];
	for(int k=1; k<=18; k++)
			for(int i=1; i<=n; i++)
				below[i][k] = below[below[i][k-1]][k-1];
	
	for(int i=1; i<=n; i++){
		int j=i;
		if(a[q[i]] > a[i] && AboveOK(i,q[i])){
			for(int k=18; k>=0; k--)
				if(above[j][k] && AboveOK(above[j][k],q[i])) j = above[j][k];
			j = above[j][0];
		}
		if(a[q[i]] < a[i] && BelowOK(i,q[i])){
			for(int k=18; k>=0; k--)
				if(below[j][k] && BelowOK(below[j][k],q[i])) j = below[j][k];
			j = below[j][0];
		}
		Fraction ans = Cross(j,q[i]);
		if(!ans) printf("-1\n");
		else ans.Print();
	}
	return 0;
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

inline int GCD(int x, int y){
	return y? GCD(y, x%y) : x;
}

Fraction::Fraction(int up, int down){
	nume = up;
	deno = down;
}

inline Fraction Fraction::Reverse(){
	if(nume <= 0){
		nume *= -1;
		deno *= -1;
	}
	if(deno <= 0) return Fraction(INT_MAX, 1);
	int factor = GCD(nume, deno);
	return Fraction(nume / factor, deno / factor);
}

inline Fraction Cross(int x, int y){
	return Fraction(a[x] - a[y], x - y).Reverse();
}

inline void Fraction::Print(){
	printf("%lld/%lld\n", nume, deno);
	return;
}

inline bool cmp(int x, int y){
	return a[x] < a[y];
}

inline bool AboveOK(int x, int y){
	if(!above[x][0]) return false;
	Fraction tmp = Cross(above[x][0],x);
	return (a[x] - a[y]) * tmp.deno <= tmp.nume * (x-y);
}

inline bool BelowOK(int x, int y){
	if(!below[x][0]) return false;
	Fraction tmp = Cross(below[x][0],x);
	return (a[x] - a[y]) * tmp.deno >= tmp.nume * (x-y);
}