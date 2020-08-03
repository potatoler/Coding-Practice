#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 1005;
int m, n, A, B, C, D, ans, deque[MaxN], g[MaxN][MaxN], fl[MaxN][MaxN], gr[MaxN][MaxN], p[MaxN][MaxN], q[MaxN][MaxN];
int main(){
	scanf("%d%d%d%d%d%d",&m,&n,&A,&B,&C,&D);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&g[i][j]);
			g[i][j] = g[i][j] + g[i-1][j] + g[i][j-1] - g[i-1][j-1];
		}
	for(int i=C+1;i<m;i++)
		for(int j=D+1;j<n;j++)
			fl[i][j] = g[i][j] - g[i-C][j] - g[i][j-D] + g[i-C][j-D];
	for(int i=A;i<=m;i++)
		for(int j=B;j<=n;j++)
			gr[i][j] = g[i][j] - g[i-A][j] - g[i][j-B] + g[i-A][j-B];
	for(int i=C+1;i<m;i++){
		int head = 1, tail = 0;
		for(int j = D+1;j<n;j++){
			while(head <= tail && deque[head] < j-B+D+2) head++;
			while(head <= tail && fl[i][deque[tail]] >= fl[i][j]) tail--;
			deque[++tail] = j;
			if(j >= B-1) p[i][j+1] = fl[i][deque[head]];
		}
	}
	for(int j=B;j<=n;j++){
		int head = 1, tail = 0;
		for(int i=C+1;i<m;i++){
			while(head <= tail && deque[head] < i-A+C+2) head++;
			while(head <= tail && p[deque[tail]][j] >= p[i][j]) tail--;
			deque[++tail] = i;
			if(i >= A-1) q[i+1][j] = p[deque[head]][j];
		}
	}
	for(int i=A;i<=m;i++)
		for(int j=B;j<=n;j++)
			ans = max(ans, gr[i][j] - q[i][j]);
	printf("%d",ans);
	return 0;
}