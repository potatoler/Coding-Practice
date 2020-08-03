#include<iostream>
#include<cstdio>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1000010;
int n, a, b, c, f[MaxN], sum[MaxN], deque[MaxN];
#define k(x) (2 * a * sum[x])
#define b(x) (f[x] - a * sum[x] * sum[x] - b * sum[x] - c)
#define x(x) sum[x]
#define y(x) (f[x] + a * sum[x] * sum[x] - b * sum[x])

inline double Slope(int i, int j){
	return 1.0 * (y(i) - y(j)) / (x(i) - x(j));
}

signed main(){
	scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
	for(int i=1;i<=n;i++){
		scanf("%lld", &sum[i]);
		sum[i] += sum[i-1];
	}
	int head = 0, tail = 0;
	for(int i=1;i<=n;i++){
		while(head < tail && Slope(deque[head], deque[head+1]) > k(i)) head++;
		f[i] = -(k(i) * x(deque[head]) - y(deque[head]) - a * sum[i] * sum[i]-b * sum[i] - c);
		while(head < tail && Slope(deque[tail-1], deque[tail]) <= Slope(deque[tail], i)) tail--;
		deque[++tail] = i;
	}
	printf("%lld", f[n]);
	return 0;
}