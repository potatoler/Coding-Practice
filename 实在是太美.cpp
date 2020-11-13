#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, a[MaxN], b[MaxN];
priority_queue<int, vector<int>, greater<int> > q;

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
	for(int i=1; i<=n; i++)
		a[i] = Read();
	for(int i=1; i<=n; i++)
		b[i] = Read();
	int ans = a[1] + b[2];
	q.push(a[2]-b[2]);
	for(int i=3; i<=n; i+=2){
		int value = q.top();
		if(value + b[i] + b[i+1] <= a[i] + b[i+1]){
			ans += value + b[i] + b[i+1];
			q.pop();
			q.push(a[i] - b[i]);
			q.push(a[i+1] - b[i+1]);
		}
		else{
			ans += a[i] + b[i+1];
			q.push(a[i+1] - b[i+1]);
		}
	}
	printf("%lld", ans);
	return 0;
}