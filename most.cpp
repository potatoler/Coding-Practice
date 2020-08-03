#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
int lim,ans;
bool flag; 
int num[1010],tot[1010]; 
ll gcd(ll a,ll b){
    return b==0?a:gcd(b,a%b);
}
void dfs(ll dep,ll mol,ll den,ll pre){
    if(dep==lim+1){
        if(mol==0){
            flag=true; 
            if(num[lim]<tot[lim]){
                for(ll i=1;i<=lim;i++)
                    tot[i]=num[i];
                ans=num[lim]; 
            }
        }   
        return;
    }
    for(ll i=max(pre,den/mol);i<=den*(lim+1-dep)/mol;i++){
        if((den*(lim+1-dep))/mol>ans&&num[dep]<ans)break; 
        num[dep]=i; 
        ll g=gcd(mol*i-den,den*i);
        dfs(dep+1,(mol*i-den)/g,(den*i)/g,i+1); 
    }
}
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    for(lim=1;;lim++){
        tot[lim]=0x3f3f3f3f; 
        ans=0x3f3f3f3f;
        dfs(1,a,b,1);
        if(flag)break; 
    }
    for(ll i=1;i<=lim;i++)
        printf("%d ",tot[i]);
    return 0;
}
