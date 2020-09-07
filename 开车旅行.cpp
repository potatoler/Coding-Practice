#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 100005;
double MinValue = 1.0 * INT_MAX;
int n, m, h[MaxN], nextA[MaxN], nextB[MaxN], distA[MaxN], distB[MaxN];

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
		h[i] = Read();
	for(int i=n-1; i>=1; i--){
		int veryMin = i+1, secondMin = 0;
		distB[i] = abs(h[i] - h[i+1]);
		for(int j=i+2; j<=n; j++){
			if(distB[i] > abs(h[i] - h[j]) || (distB[i] == abs(h[i] - h[j]) && h[j] < h[veryMin])){
				distA[i] = distB[i];
				distB[i] = abs(h[i] - h[j]);
				secondMin = veryMin;
				veryMin = j;
			}
			else if(distA[i] == 0 || distA[i] > abs(h[i] - h[j]) || (distA[i] == abs(h[i] - h[j]) && h[j] < h[secondMin])){
				distA[i] = abs(h[i] - h[j]);
				secondMin = j;
			}
		}
		nextB[i] = veryMin;
		nextA[i] = secondMin;
	}
	int x = Read(), ans = 0;
	for(int i=1; i<=n; i++){
		int a = 0, b = 0, local = i, turn = 0;
		while(true){
			if(turn){
				if(a + b + distB[local] > x || !nextB[local]) break;
				b += distB[local];
				local = nextB[local];
			}
			else{
				if(a + b + distA[local] > x || !nextA[local]) break;
				a += distA[local];
				local = nextA[local];
			}
			turn ^= 1;
		}
		if(!ans || 1.0*a/b - 1.0*MinValue < -0.00000001 || (fabs(1.0*a/b - 1.0*MinValue) <= 0.00000001 && h[ans] < h[i])){
			MinValue = 1.0*a/b;
			ans = i;
		}
	}
	// for(int i=1; i<=n; i++)
	// 	printf("%lld %lld\n", distB[i], distA[i]);
	printf("%lld\n", ans);
	m = Read();
	while(m--){
		int local = Read(), x = Read(), a = 0, b = 0, turn = 0;
		while(true){
			if(turn){
				if(a + b + distB[local] > x || !nextB[local]) break;
				b += distB[local];
				local = nextB[local];
			}
			else{
				if(a + b + distA[local] > x || !nextA[local]) break;
				a += distA[local];
				local = nextA[local];
			}
			turn ^= 1;
		}
		printf("%lld %lld\n", a, b);
	}
	return 0;
}