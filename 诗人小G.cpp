#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
#define double long double
using namespace std;
const int MaxN = 100005;
int N, L, P, sum[MaxN], pre[MaxN], k[MaxN], queue[MaxN], head, tail;
double f[MaxN];
char str[MaxN][31];

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

inline double QuickPower(double base){
	double ans = 1;
	int x = P;
	while(x){
		if(x&1) ans *= base;
		base *= base;
		x >>= 1;
	}
	return ans;
}

inline double Calculate(int x, int y){
	return f[y] + QuickPower((double)abs(sum[x]-sum[y]-L));
}

inline int Find(int x, int y){
	int l = x, r = N + 1;
	while(l < r){
		int mid = (l + r) >> 1;
		if(Calculate(mid, x) >= Calculate(mid, y)) r = mid;
		else l = mid+1;
	}
	return l;
}

signed main(){
	int T = Read();
	while(T--){
		N = Read(), L = Read()+1, P = Read();
		for(int i=1; i<=N; i++){
			scanf("%s", str[i]);
			sum[i] = sum[i-1] + strlen(str[i])+1;
		}
		head=tail=1;
		queue[1] = 0;
		for(int i=1; i<=N; i++){
			while(head < tail && k[head] <= i) head++;
			f[i] = Calculate(i, queue[head]);
			pre[i] = queue[head];
			while(head < tail && k[tail-1] >= Find(queue[tail], i)) tail--;
			k[tail] = Find(queue[tail], i);
			queue[++tail] = i;
		}
		if(f[N] > 1e18) puts("Too hard to arrange");
		else{
			printf("%.0Lf\n", f[N]);
			tail = 0;
			queue[tail] = N;
			for(int i = N; i; i = pre[i]) queue[++tail] = pre[i];
			while(tail){
				for(int i = queue[tail]+1; i<queue[tail-1]; i++)
					printf("%s ", str[i]);
				puts(str[queue[tail-1]]);
				tail--;
			}
		}
		puts("--------------------");
	}
	return 0;
}