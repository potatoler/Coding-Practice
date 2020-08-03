#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
long long a,b,p[20],ans;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
void dfs(int cnt,int stp,ll d){
	if(d>b) return;
	if(stp==n+1){
		if(cnt&1) ans-=b/d-(a-1)/d;
		else ans+=b/d-(a-1)/d;
		return;
	}
	dfs(cnt,stp+1,d);
	dfs(cnt+1,stp+1,d*p[stp]/gcd(d,p[stp]));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&p[i]);
	scanf("%lld%lld",&a,&b);
	dfs(0,1,6);
	printf("%lld",ans);
	return 0;
}