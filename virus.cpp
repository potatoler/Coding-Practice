#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define lowbit(x) x&(-x)
#define mem(a,b) memset(a,b,sizeof(a))
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
const int maxn=300005;
struct node{
    ll to,next,w;
}edge[maxn*2];
ll n,k;
ll head[maxn],tot;
ll sum,f[maxn],vis[maxn],son[maxn],core,deep[maxn],d[maxn];
ll ans;
void init(){
    mem(head,-1);
    mem(vis,0);
    tot=0;
    ans=0;
}

void add(ll a,ll b,ll c){
    edge[tot].to=b,edge[tot].next=head[a],edge[tot].w=c;
    head[a]=tot++;
}

void getcore(ll u,ll fa){
    son[u]=1,f[u]=0;
    for(ll i=head[u];i!=-1;i=edge[i].next){
        ll v=edge[i].to;
        if(v==fa||vis[v]) continue;
        getcore(v,u);
        son[u]+=son[v],f[u]=max(f[u],son[v]);
    }
    f[u]=max(f[u],sum-son[u]);
    if(f[u]<f[core]) core=u;
}

void getdeep(ll u,ll fa){
    deep[++deep[0]]=d[u];
    for(ll i=head[u];i!=-1;i=edge[i].next){
        ll v=edge[i].to,w=edge[i].w;
        if(v==fa||vis[v]) continue;
        d[v]=d[u]+w;
        getdeep(v,u);
    }
}

ll cal(ll u,ll w){
    deep[0]=0,d[u]=w,getdeep(u,0);
    ll tmp=0;
    sort(deep+1,deep+deep[0]+1);
    for(ll l=1,r=deep[0];l<r;)
        if(deep[l]+deep[r]<=k) tmp+=(r-l),l++;
        else r--;
    return tmp;
}

void work(ll u){
    ans+=cal(u,0);
    vis[u]=1;
    for(ll i=head[u];i!=-1;i=edge[i].next){
        ll v=edge[i].to,w=edge[i].w;
        if(vis[v]) continue;
        ans-=cal(v,w);
        sum=son[v];
        core=0;
        getcore(v,core);
        work(core);
    }
}

int main(){
	scanf("%lld%lld",&n,&k);
        init();
        for(ll i=0;i<n-1;i++){
            ll a,b,c;
            scanf("%lld%lld%lld",&a,&b,&c);
            add(a,b,c),add(b,a,c);
        }
        core=0,sum=n,f[0]=INF;
        getcore(1,0);
        work(core);
        printf("%lld\n",ans);
    return 0;
}