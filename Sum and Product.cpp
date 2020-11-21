#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
using namespace std;

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
	int s = Read(), p = Read();
	for(int i=1; i*i<=p; i++){
		if(p % i) continue;
		else{
			if(i + (p/i) == s){
				printf("Yes\n");
				return 0;
			}
		}
	}
	printf("No\n");
	return 0;
}