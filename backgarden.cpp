#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int mod=1000000007;
const int maxn=1314520;
typedef long long ll;
bool r[maxn][maxn];
int n;
ll cnt;
ll fac(ll x){  
	if(x==1) return 1;
	else return x*=fac(x-1)%mod;  
}  
void dfs(int x){
	if(x==n+1){
		cnt++;
		cnt%=mod;
		return;
	}
	for(int i=1;i<=n;i++)
		if(r[x][i]==false){
			for(int j=1;j<=n;j++)
				r[j][i]=true;
			dfs(x+1);
			for(int j=1;j<=n;j++)
				if(j!=i) r[j][i]=false;
		}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		r[i][i]=true;
	dfs(1);
	cnt*=fac((ll)n);
	printf("%lld\n",cnt%mod);
	return 0;
}