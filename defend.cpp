#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100005;
int a[maxn],n,m;
bool chieku(long long x){
    int p=0;long long sum;
    for(int i=1;i<=m;i++){
        sum=0;
        while(sum<x){
            if(p>n) return false;
            sum+=a[++p];
        }
    }
    return true;
}
int main(){
    scanf("%d%d",&n,&m);
    long long l=0,r=0,mid=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),r+=a[i];
    while(r-l>1){
        mid=(l+r)/2;
        if(chieku(mid)) l=mid;
        else r=mid;
    }
    printf("%lld\n",l);
    return 0;
}