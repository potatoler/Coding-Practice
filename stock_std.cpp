#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int ansa,ansb,n;
int a[5001],dp[5001],len[5001];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<=i;j++){
            if(a[i]<a[j])dp[i]=max(dp[i],dp[j]+1);
        }
        ansa=max(ansa,dp[i]);
    }
    
    cout<<ansa<<endl;
    return 0;
}