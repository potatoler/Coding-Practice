#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, m, nums[MaxN], a[MaxN], p[MaxN], cnt[MaxN], idx[MaxN], tmp[MaxN], sum[MaxN];

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
	if(l>=r) return;
	int mid = (l+r) >> 1;
	MergeSort(l, mid), MergeSort(mid+1, r);
	int i = mid, j = r, k = r;
	int cntLeft = mid-l+1, cntRight = r-mid;
	while(i>=l && j>=mid+1) {
		if(a[idx[i]] > a[idx[j]]) {
			cnt[idx[i]] += cntRight;
			tmp[k--] = idx[i--];
			cntLeft--;
		}
		else{
			tmp[k--] = idx[j--];
			cntRight--;
		}
	}
	while(i>=l)
		tmp[k--] = idx[i--];
	while(j>=mid+1)
		tmp[k--] = idx[j--];
	for(i=l; i<=r; i++) 
		idx[i] = tmp[i];
	return;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		nums[i] = a[i] = Read();
		idx[i] = i;
	}
	MergeSort(1, n);
	for(int i=n; i>=0; i--)
		sum[i] = sum[i+1] + cnt[i];
	while(m--){
		int pos = Read();
		if(cnt[pos] != 0){
			for(int i = pos; i<=n; i++){
				if(nums[i] <= nums[pos]){
					sum[0] -= cnt[i];
					cnt[i] = 0;
				}
			}
		}
		printf("%lld\n", sum[0]);
	}
	return 0;
}