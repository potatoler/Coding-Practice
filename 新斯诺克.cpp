#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, value[MaxN], tmp[MaxN], sum[MaxN], ans;

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

inline void MergeSort(int l, int r){
	if(l == r) return;
	int mid = (l+r) >> 1;
	MergeSort(l,mid), MergeSort(mid+1,r);
	int p = l, q = mid+1;
	int pos = l;
	while(p <= mid && q <= r){
		if(value[p] > value[q]){
			ans += mid - p + 1;
			tmp[pos++] = value[q++];
		}
		else tmp[pos++] = value[p++];
	}
	while(p <= mid) tmp[pos++] = value[p++];
	while(q <= r) tmp[pos++] = value[q++];
	for(int i=l; i<=r; i++)
		value[i] = tmp[i];
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		int x = Read();
		sum[i] = sum[i-1] + x;
		value[i] = -sum[i] + i * m;
	}
	value[0] = 0;
	MergeSort(0, n);
	printf("%lld", ans);
	return 0;
}