#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<vector>
#define int long long
using namespace std;
int T, a, b, c, d;

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
		int ans = 0;
		a = Read(), b = Read(), c = Read(), d = Read();
		if(a == b && b == c && c == d){
			printf("1\n");
			continue;
		}
		else if((a==b && c==d) || (a==c&&b==d) || (a==d&&b==c)){
			printf("4\n");
			continue;
		}
		else if(a+b == c+d || a+c == b+d || a+d == b+c){
			printf("8\n");
			continue;
		}
		else{
			printf("0\n");
			continue;
		}
	}
	return 0;
}