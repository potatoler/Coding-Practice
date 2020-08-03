#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
const int MaxN = 400005;
int f[MaxN], a[MaxN], n, l, r;
int queue[MaxN], ans = -0x3f3f3f3f;

int main(){
	scanf("%d%d%d",&n, &l, &r);
	if(l > r) swap(l,r);
	for(int i=0;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n+r;i++)
		f[i] = -0x3f3f3f3f;
	int head = 1, tail = 0;
	for(int i=l;i<=n;i++){
		while(head <= tail && queue[head] < i-r) head++;
		while(head <= tail && f[queue[tail]] < f[i-l]) tail--;
		queue[++tail] = i-l;
		f[i] = f[queue[head]] + a[i];
		if(i + r > n)
			ans = max(f[i], ans);
	}
	printf("%d\n",ans);
}