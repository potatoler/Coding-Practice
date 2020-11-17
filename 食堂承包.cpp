#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 10004, MaxM = 400005;
priority_queue<int, vector<int>, greater<int> > q;
int n, m, w[MaxN], ans;

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
		int x = Read();
		q.push(x);
	}
	m = Read();
	for(int i=1; i<=m; i++)
		w[i] = Read();
	sort(w+1, w+1+n);
	int p = 1;
	while(p<=m && q.size()){
		int top = q.top();
		q.pop();
		if(top >= w[p]){
			top -= w[p];
			p++, ans++;
			if(top) q.push(top);
		}
	}
	printf("%lld", ans);
	return 0;
}