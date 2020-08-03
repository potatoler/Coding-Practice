#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 50005;
int n, m, original[MaxN], discrete[MaxN], bucket[MaxN];

inline int Read(){
	char x; int num;
	while(x = getchar(), x < '0' || x > '9');
	num = x - '0';
	while(x = getchar(), x >= '0' && x <= '9'){
		num *= 10;
		num += x - '0';
	}
	return num;
}

inline void Write(int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9) Write(x/10);
    putchar(x % 10 + '0');
}

signed main(){
	n = Read(), m = Read();
	for(int i=1;i<=n;i++)
		discrete[i] = original[i] = Read();
	sort(original + 1, original + 1 + n);
	int sum = unique(original + 1, original + 1 + n) - original - 1;
	for(int i=1;i<=n;i++)
		discrete[i] = lower_bound(original + 1, original + 1 + sum, discrete[i]) - original;
	int tmp = 0;
	while(m--){
		int ori_l = Read(), ori_r = Read();
		int l = (ori_l + tmp - 1) % n + 1;
		int r = (ori_r + tmp - 1) % n + 1;
		if(l > r) swap(l, r);
		for(int i=l;i<=r;i++)
			bucket[discrete[i]]++;
		int mx = 0, p = 0;
		for(int i=1;i<=sum;i++){
			if(mx < bucket[i]){
				mx = bucket[i];
				p = i;
			}
		}
		Write(original[p]); printf("\n");
		tmp = original[p];
		memset(bucket, 0, sizeof(bucket));
	}
	return 0;
}