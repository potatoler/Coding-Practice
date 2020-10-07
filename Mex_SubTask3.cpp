#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
bool flag = false;
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
	int n = Read(), m = Read();
	while(m--){
		int l = Read(), r = Read(), val = Read();
		if(l == 0 && val == 0) flag = 1;
	}
	if(flag) printf("-1");
	else{
		for(int i=0; i<=n; i++)
			printf("%lld ", i);
	}
	return 0;
}