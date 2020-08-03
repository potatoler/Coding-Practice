#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100010;
int n, m, a[MaxN], sum[MaxN], ans[MaxN], maxn = 0;

struct Range{
	int r, ID, p, q, op;
}range[MaxN*2];

bool cmp(Range a, Range b){
	return a.r < b.r;
}

void NewRange(int i, int l, int r, int p, int q){
//	range[i] = {l-1, i, p, q, -1};
//	range[i+m] = {r, i, p, q, 1};
	range[i].r = l-1;
	range[i].ID = i;
	range[i].p = p;
	range[i].q = q;
	range[i].op = -1;
	range[i+m].r = r;
	range[i+m].ID = i;
	range[i+m].p = p;
	range[i+m].q = q;
	range[i+m].op = 1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		int l, r, p, q;
		scanf("%d%d%d%d",&l,&r,&p,&q);
		NewRange(i, l, r, p, q);
	}
	sort(range+1, range+1+m*2, cmp);
	int tail = 0;
	for(int i=1;i<=m*2;i++){
		while(tail < range[i].r){
			tail++;
			sum[a[tail]]++;
			maxn = max(maxn, a[tail]);
		}
		for(int j=0;j*range[i].p+range[i].q<=maxn;j++){
			ans[range[i].ID] += sum[j*range[i].p+range[i].q] * range[i].op;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}