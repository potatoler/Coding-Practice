#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define int long long
using namespace std;
priority_queue<int, vector<int>, less<int> > bigger;
priority_queue<int, vector<int>, greater<int> > smaller;
int n, k, p;

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

inline void Add(int x){
	if(smaller.size() < k) smaller.push(x);
	else{
		if(smaller.size() && smaller.top() < x){
			bigger.push(smaller.top());
			smaller.pop();
			smaller.push(x);
		}
		else bigger.push(x);
	}
}

signed main(){
//	freopen("queue.in", "r", stdin);
//	freopen("queue.out", "w", stdout);
	n = Read(), k = Read(), p = Read();
	int last = 0;
	while(n--){
		int op = Read();
		if(op == 1){
			int x = Read();
			if(p == 1) x ^= last;
			Add(x);
		}
		else{
			last = smaller.top();
			printf("%lld\n", last);
			smaller.pop();
			if(bigger.size()){
				smaller.push(bigger.top());
				bigger.pop();
			}
		}
	}
	return 0;
}