#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 50004;
int T, n, k, a[MaxN], ans;

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

inline int mex(int x, int y){
	if(min(x,y) > 0) return 0;
	else return max(x,y) == 1? 2:1;
}

inline int SG(int x){
	if(x & 1) return x <= 3;
	return mex(SG(x-1), SG(x/2));
}

signed main(){
	T = Read();
	while(T--){
		ans = 0;
		n = Read(), k = Read();
		for(int i=1; i<=n; i++)
			a[i] = Read();
		if(k % 2) for(int i=1; i<=n; i++)
			ans ^= SG(a[i]);
		else for(int i=1; i<=n; i++)
			if(a[i] <= 2) ans ^= a[i];
			else if(!(a[i]&1)) ans ^= 1;
		puts(ans? "Alice" : "Bob");
	}
	return 0;
}