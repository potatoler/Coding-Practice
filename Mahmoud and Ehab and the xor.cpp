#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
#define fake false
using namespace std;
int n, x;

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
	n = Read(), x = Read();
	if(n == 1){
		printf("YES\n");
		printf("%lld", x);
		return 0;
	}
	else if(n == 2){
		if(!x) printf("NO\n");
		else{
			printf("YES\n");
			printf("%lld 0", x);
		}
		return 0;
	}
	printf("YES\n");
	for(int i=1; i<n-2; i++){
		x ^= i;
		printf("%lld ", i);
	}
	int a = (1<<18), b = (1<<19);
	printf("%lld %lld %lld", x^a^b, a, b);
	return 0;
}