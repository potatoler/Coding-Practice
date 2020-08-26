#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int MaxA = 100005;
int n, bucket[MaxA], ans;
queue<int> sortQ, mergeQ;

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
		int a = Read();
		bucket[a]++;
	}
	for(int i=1; i<=100000; i++){
		while(bucket[i]){
			sortQ.push(i);
			bucket[i]--;
		}
	}
	for(int i=1; i<n; i++){
		int x, y;
		if(mergeQ.empty() || (sortQ.front() < mergeQ.front() && !sortQ.empty())){
			x = sortQ.front();
			sortQ.pop();
		}
		else{
			x = mergeQ.front();
			mergeQ.pop();
		}
		if(mergeQ.empty() || (sortQ.front() < mergeQ.front() && !sortQ.empty())){
			y = sortQ.front();
			sortQ.pop();
		}
		else{
			y = mergeQ.front();
			mergeQ.pop();
		}
		ans += x+y;
		mergeQ.push(x+y);
	}
	printf("%lld", ans);
	return 0;
}