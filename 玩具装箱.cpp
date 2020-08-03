#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
const int maxn=50010;
int n,L;
double sum[maxn],dp[maxn];
int head,tail,Q[maxn];
inline double a(int i){return sum[i]+i;}
inline double b(int i){return a(i)+L+1;}
inline double X(int i){return b(i);}
inline double Y(int i){return dp[i]+b(i)*b(i);}
inline double slope(int i,int j){return (Y(i)-Y(j))/(X(i)-X(j));}

signed main(){
	scanf("%lld%lld",&n,&L);
	for(int i=1;i<=n;i++){
		scanf("%lf",&sum[i]);
		sum[i] += sum[i-1];
	}
	head = tail = 1;
	for(int i=1;i<=n;i++){
		while(head < tail && slope(Q[head], Q[head+1]) < 2*a(i)) ++head;
		dp[i] = dp[Q[head]] + (a(i) - b(Q[head])) * (a(i) - b(Q[head]));
		while(head < tail && slope(i, Q[tail-1]) < slope(Q[tail-1],Q[tail])) --tail;
		Q[++tail] = i;
	}
	printf("%.lf\n",dp[n]);
	return 0;
}