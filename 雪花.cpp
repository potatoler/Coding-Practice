#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxW = 50004, MaxH = 102;
int w, h, ans, sum;
char snow[MaxH][MaxW];
int sum1[MaxW], sum2[MaxW];

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
	w = Read(), h = Read()-1;
	for(int i=h; i>=0; i--)
		scanf("%s", snow[i]+1);
	for(int i=1; i<=w; i++){
		for(int j=0; i+j<=w && j<=h; j++){
			sum1[i] += snow[j][i+j] == '*'? 1 : 0;
		}
	}
//	for(int i=1; i<=w; i++)
//		printf("%lld ", sum1[i]);
	for(int i=w; i>=1; i--){
		for(int j=0; i-j>=1 && j<=h; j++){
			sum2[i] += snow[j][i-j] == '*'? 1 : 0;
		}
	}
//	printf("\n");
//	for(int i=1; i<=w; i++)
//		printf("%lld ", sum2[i]);
	for(int i=0; i<=h; i++){
		for(int j=1; j<=i+1 && j<=w; j++){
			if(snow[i][j] == '*') sum++;
		}
	}
	ans = sum;
	for(int i=2; i<=w; i++){
		sum += sum1[i];
		sum -= sum2[i-1];
//		ans += snow[i][0] == '*'? 1 : 0;
		ans = max(ans, sum);
//		printf("%lld", ans);
	}
	printf("%lld", ans);
	return 0;
}