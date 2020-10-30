#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
#define fake false
using namespace std;
const int MaxN = 10000007;
int a, b, prime[MaxN], cnt, sum[MaxN], visited[MaxN];

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

inline void Init(){
	for(int i=2; i<MaxN; i++){
		if(!visited[i]){
			sum[i] = visited[i] = i;
			prime[++cnt] = i;
		}
		for(int j=1; j<=cnt && prime[j]*i < MaxN; j++){
			if(prime[j] > visited[i]) break;
			visited[i * prime[j]] = prime[j];
			if(!sum[i*prime[j]]){
				if(sum[i] == 1 || sum[prime[j]] == 1){
					sum[i*prime[j]] = 1;
					continue;
				}
				if(visited[i] == visited[prime[j]]) sum[i*prime[j]] = visited[i];
				else sum[i*prime[j]] = 1;
			}
		}
	}
	for(int i=1; i<MaxN; i++)
		sum[i] += sum[i-1];
	return;
}

signed main(){
	Init();
	a = Read(), b = Read();
	printf("%lld", sum[b] - sum[a-1]);
	return 0;
}