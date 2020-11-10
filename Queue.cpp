#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006;
char str[MaxN];

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
	scanf("%s", str+1);
	int len = strlen(str+1);
	int ans = 0, danshi = 0;
	for(int i=1; i<=len; i++){
		switch(str[i]){
			case 'M':{
				danshi++;
				break;
			}
			case 'F':{
				if(danshi > 0) ans = max(ans+1, danshi);
				break;
			}
		}
	}
	printf("%lld", ans);
	return 0;
}