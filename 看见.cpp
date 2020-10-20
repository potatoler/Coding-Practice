#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, upans, cntpos;
map<int,int> idx[MaxN];
struct Line{
	int k, m, serial;
	bool seen;
	bool operator < (const Line &b) const {
		return m < b.m;
	}
}line[MaxN];
struct pos{
	bool kind;
	int sumall, max, min, sumtwo;
}pos[MaxN];

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
	for(int i=1; i<=n; i++){
		line[i].k = Read(), line[i].m = Read();
		line[i].serial = i, line[i].seen = false;
	}
	sort(line+1, line+1+n);
	
	printf("%lld", ans);
	return 0;
}