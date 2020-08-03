#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
int p[16]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
ll ans,n;
int mx;
void dfs(int dep,ll tmp,int num){ 
  if(tmp>n||dep>14)return;
  if(num>mx) ans=tmp,mx=num;
  if(num==mx&&ans>tmp) ans=tmp;  
  for(int i=1;i<=63;i++){
    if(tmp>n/p[dep]) break;
    dfs(dep+1,tmp*=p[dep],num*(i+1));
  } 
}
int main(){
    while(scanf("%lld",&n)){
        ans=1;
        mx=1;
        dfs(0,1,1);
        printf("%lld\n",ans);
    }
    return 0;
}