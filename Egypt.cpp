#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=105;
ll a,b,maxd;
ll tmp[maxn],ans[maxn];
ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}
ll saishou(ll a,ll b){
	return b/a+1;
}
bool yoriyoi(int x){
	for(int i=x;i>=0;i--)
		if(tmp[i]!=ans[i]) return ans[i]==-1||tmp[i]<ans[i];
	return false;
}
bool dfs(int dpth,ll mn,ll aa,ll bb){
	if(dpth==maxd){
		if(bb%aa) return false;
		tmp[dpth]=bb/aa;
		if(yoriyoi(dpth)) memcpy(ans,tmp,sizeof(ll)*(dpth+1));
		return true;
	}
	bool deki=false;
	mn=max(mn,saishou(aa,bb));
	for(int i=mn;;i++){
		if(bb*(maxd+1-dpth)<=i*aa) break;
		tmp[dpth]=i;
		ll nxtb=b*i,nxta=aa*i-bb,g=gcd(nxta,nxtb);
		if(dfs(dpth+1,i+1,nxta/g,nxtb/g)) deki=true;
	}
	return deki;
}
int main(){
	scanf("%lld%lld",&a,&b);
	if(b%a==0){
		printf("%lld",b/a);
		return 0;
	}
	for(maxd=1;maxd<=100;maxd++){
		memset(ans,-1,sizeof(ans));
		if(dfs(0,saishou(a,b),a,b)) break;
	}
	for(int i=0;i<maxd;i++)
		printf("%lld ",ans[i]);
	return 0;
}