#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1003, ln = MaxN*8;
int k, q;
double f[MaxN], g[ln];

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
	f[0] = 1.0;
	for(int i=1; i<ln; i++){
		for(int j=k; j>=1; j--){
			f[j] = (f[j-1] * (k-j+1) + f[j] * j) / (k * 1.0);
		}
		g[i] = f[k];
		f[0] = 0;
	}
	return;	
}

signed main(){
	k = Read(), q = Read();
	Init();
	while(q--){
		double p;
		scanf("%lf", &p);
		p /= 2000;
		for(int i=1; i<ln; i++){
			if(g[i] >= p){
				printf("%lld\n", i);
				break;
			}
		}
	}
	return 0;
}