#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
typedef long long ll; 
const int N=2020,M=1000000,MAX=1000010,MOD=1000000007;
struct node{
	int x,y;
}a[N];
int n,h,w;
ll f[N],fac[MAX],inv[MAX];
 
inline bool cmp(node x,node y){
	if(x.x==y.x) return x.y<y.y;
	return x.x<y.x; 
}

inline ll power(ll x,ll ent){
	ll ans=1;
	while(ent){
		if(ent&1) ans=ans*x%MOD;
		ent>>=1;
		x=x*x%MOD;
	}
	return ans%MOD;
}
 
inline ll C(ll x,ll y){
	if(x<y) return 0;
	return fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}
 
int main(){
	scanf("%d%d%d",&h,&w,&n); 
	h=h-1; w=w-1;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].x-=1; a[i].y-=1;	 
	}
	a[0].x=a[0].y=0; 
	a[++n].x=h; a[n].y=w;
	sort(a+1,a+n+1,cmp); 
	fac[0]=1;
	for(ll i=1;i<=M;i++) 		 
		fac[i]=1ll*fac[i-1]*i%MOD;
	inv[0]=1;inv[M]=power(fac[M],MOD-2);
	for(ll i=M-1;i>=1;i--) 
		inv[i]=1ll*inv[i+1]*(i+1)%MOD; 
	for(int i=1;i<=n;i++){ 
		f[i]=C(a[i].x+a[i].y,a[i].x);
		if(f[i]==0) continue;
		for(int j=1;j<i;j++){
			f[i]-=(f[j]*C(a[i].x-a[j].x+a[i].y-a[j].y,a[i].x-a[j].x))%MOD;
			f[i]%=MOD;
			f[i]+=MOD; f[i]%=MOD;
		} 
	} 
	printf("%lld\n",f[n]);
	return 0;
} 