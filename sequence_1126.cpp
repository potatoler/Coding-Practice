//给定一列数，至少改变几个数可以将原数列变成等差数列？
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<map>
//#define int long long
using namespace std;
const int MaxN = 300000;
int n, w, a[MaxN], ans = INT_MAX;

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
	n = Read(), w = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	if(n == 1){
		printf("0");
		return 0;
	}
	for(int d=0; d*(n-1)<=w; d++){
		map<int,int> record;
		for(int i=1; i<=n; i++){
			int a1 = a[i] - d*(i-1);
			if(a1 > 0 && a1 + d * (n-1) <= w) record[a1]++;
		}
		for(auto i:record)
			ans = min(ans, n-i.second);
	}
	printf("%d", ans);
	return 0;
}