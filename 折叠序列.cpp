#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 102;
int f[MaxN][MaxN], cost[MaxN];
char a[MaxN];

inline bool Unfoldable(int zipl, int zipr, int l, int r){
	int len = zipr - zipl + 1;
	if((r-l+1) % len) return false;
	for(int i=0; i<r-l+1; i++)
		if(a[l+i] != a[zipl+(i%len)]) return false;
	return true;
}

inline void PrintAnswer(int l, int r){
	if(f[l][r] == r-l+1){
		for(int i=l; i<=r; i++)
			printf("%c", a[i]);
		return;
	}
	for(int i=l; i<r; i++){
		if(f[l][r] == f[l][i] + f[i+1][r]){
			PrintAnswer(l,i);
			PrintAnswer(i+1,r);
			return;
		}
		if(Unfoldable(l,i,l,r) && f[l][r] == f[l][i] + cost[(r-l+1)/(i-l+1)]+2){
			printf("%lld(", (r-l+1)/(i-l+1));
			PrintAnswer(l,i);
			printf(")");
			return;
		}
	}
}

signed main(){
	for(int i=1; i<=99; i++)
		cost[i] = i>=10? 2 : 1;
	cost[100] = 3;
	scanf("%s", a+1);
	int length = strlen(a+1);
	for(int i=1; i<=length; i++)
		f[i][i] = 1;
	for(int len=2; len<=length; len++){
		for(int l=1; l+len-1<=length; l++){
			int r = l+len-1;
			f[l][r] = r-l+1;
			for(int k=l; k<r; k++){
				f[l][r] = min(f[l][r], f[l][k]+f[k+1][r]);
				if(Unfoldable(l,k,l,r)) f[l][r] = min(f[l][r], f[l][k] + cost[(r-l+1)/(k-l+1)]+2);
			}
		}
	}
	// printf("%lld\n", f[1][length]);
	PrintAnswer(1,length);
	return 0;
}