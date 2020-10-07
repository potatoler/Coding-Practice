#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#include<vector>
#define int long long 
using namespace std;
const int MaxN = 300005;
int n, ans;
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
	for(int i=1; i<=n; i++){
		int p = Read();
		if(q.size() && q.top() < p){
			ans += (p - q.top());
			q.pop();
			q.push(p);
		}
		q.push(p);
	}
	printf("%lld", ans);
	return 0;
}