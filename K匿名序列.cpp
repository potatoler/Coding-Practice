#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<climits>
#include<cstring>
#define int long long
const int MaxN = 500005;
int n, k, T, a[MaxN], sum[MaxN], f[MaxN];
int queue[MaxN], head, tail;
inline int deltaX(int j, int k){
	return a[j+1]-a[k+1];
}
inline int deltaY(int j, int k){
	return f[j]-f[k]+sum[k]-sum[j]+j*a[j+1]-k*a[k+1];
}

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
	T = Read();
	while(T--){
		n = Read(), k = Read();
		for(int i=1; i<=n; i++){
			a[i] = Read();
			sum[i] = sum[i-1] + a[i];
		}
		head = tail = 1;
		queue[1] = 0;
		for(int i=1; i<=n; i++){
			while(head < tail && deltaY(queue[head], queue[head+1]) >= i * deltaX(queue[head], queue[head+1])) head++;
			int j = queue[head];
			// printf("%lld\n", j);
			f[i] = f[j] + sum[i] - sum[j] - (i-j)*a[j+1];
			int l = i-(k-1);
			// for(int s=head; s<=tail; s++)
			// 	printf("%lld ", queue[s]);
			// printf("\n");
			if(l >= k){
				// printf("%lld %lld\n", head, tail);
				while(head < tail){
					int x = queue[tail-1], y = queue[tail];
					if(deltaY(x,y) * deltaX(y,l) >= deltaY(y,l) * deltaX(x,y)) tail--;
					else break;
				}
				queue[++tail] = l;
			}
		}
		printf("%lld\n", f[n]);
	}
}