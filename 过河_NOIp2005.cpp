#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int stone[102], sum[10004];
bool bridge[100005];

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
	int l = Read(), s = Read(), t = Read(), m = Read();
	memset(sum, 0x3f, sizeof(sum));
	for(int i=1; i<=m; i++)
		stone[i] = Read();
	sort(stone, stone+m+2);
	int ID = 0;
	for(int i=1; i<=m+1; i++){
		if(stone[i] - stone[i-1] <= t * s) ID += stone[i] - stone[i-1];
		else ID += (stone[i] - stone[i-1]) % t + t;
		bridge[ID] = true;
	}
	sum[0] = 0;
	for(int i=1; i<=ID+t; i++)
		for(int j=s; j<=t; j++)
			if((i-j) >= 0) sum[i] = min(sum[i], sum[i-j] + bridge[i]);
	int ans = 0x3f;
	for(int i=ID; i<=ID+t; i++)
		ans = min(ans, sum[i]);
	printf("%lld", ans);
	return 0;
}