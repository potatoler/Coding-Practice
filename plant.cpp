#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=200001;
int ans,n,m;
int a[maxn],l[maxn],r[maxn];
bool bz[maxn];
struct data{
    int x;
    friend bool operator <(const data x,const data y){return a[x.x]<a[y.x];}
}t;
priority_queue <data> q;
int main(){
    scanf("%d%d",&n,&m);
    if(m>n*2){
        printf("Error!");
        return 0;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&a[t.x=i]);
        l[i]=i==1?n:i-1;
        r[i]=i==n?1:i+1;
        q.push(t);
    }
    while(m--){
        for(t=q.top(),q.pop();bz[t.x];t=q.top(),q.pop());
        ans+=a[t.x];
        a[t.x]=a[l[t.x]]+a[r[t.x]]-a[t.x];
        bz[l[t.x]]=bz[r[t.x]]=true;
        l[t.x]=l[l[t.x]];
        r[t.x]=r[r[t.x]];
        l[r[t.x]]=r[l[t.x]]=t.x;
        q.push(t);
    }
    printf("%d",ans);
    return 0;
}