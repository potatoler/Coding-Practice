#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 150000;
int n, l[MaxN], s[MaxN], ans;
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
	n = strlen(str+1);
	for(int i=1; i<=n; i++)
		l[i] = l[i-1] + (str[i] == 'L'? 1 : 0);
	for(int i=n; i>=1; i--)
		s[i] = s[i+1] + (str[i] == 'S'? 1 : 0);
	for(int i=1; i<=n; i++)
		ans += (str[i] == 'W'? 1 : 0) * l[i-1] * s[i+1];
	printf("%lld", ans);
	return 0;
}