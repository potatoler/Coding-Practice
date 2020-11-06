#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, k, a[MaxN], q[MaxN], idx[MaxN], head, tail;

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

inline void mx(){
	head = 1, tail = 0;
	for(int i=1; i<=n; i++){
		while(head <= tail && q[tail] <= a[i]) tail--;
		q[++tail] = a[i];
		idx[tail] = i;
		while(idx[head] <= i-k) head++;
		if(i >= k) printf("%lld ", q[head]);
	}
	printf("\n");
	return;
}

inline void mn(){
	head = 1, tail = 0;
	for(int i=1; i<=n; i++){
		while(head <= tail && q[tail] >= a[i]) tail--;
		q[++tail] = a[i];
		idx[tail] = i;
		while(idx[head] <= i-k) head++;
		if(i >= k) printf("%lld ", q[head]);
	}
	printf("\n");
	return;
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	mn();
	mx();
	return 0;
}