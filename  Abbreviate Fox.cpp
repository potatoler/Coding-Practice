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
const int MaxN = 200005;
int n, stack[MaxN], top, m;
char s[MaxN];

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
	n = Read();
	scanf("%s", s+1);
	for(int i=1; i<=n; i++){
		switch(s[i]){
			case 'f':{
				stack[++top] = 1;
				break;
			}
			case 'o':{
				stack[++top] = 2;
				break;
			}
			case 'x':{
				stack[++top] = 3;
				if(top >= 3){
					if(stack[top-1] == 2 && stack[top-2] == 1){
						top -= 3;
						m += 3;
					}
				}
				break;
			}
			default:{
				top = 0;
				break;
			}
		}
	}
	printf("%lld", n-m);
}