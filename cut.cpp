#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
#define N 100010
using namespace std;
 
const int yh=1e9+7;
struct info{int to,nex;}e[N*2];
int n,tot,head[N*2],c[N],in[N],cnt;
ll f[N][2],Ans;
 
inline void Link(int u,int v){
    e[++tot].to=v;
    e[tot].nex=head[u];
    head[u]=tot;
}
 
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
 
ll DP(int u,int x,int fa){
    ll &tmp=f[u][x];
    if(tmp!=-1) return tmp;
    tmp=!x;
    
    for(int i=head[u];i;i=e[i].nex){
        int v=e[i].to;
        if(v==fa) continue;
        
        if(x==0){
            if(c[v]==1) tmp=(tmp*1ll*DP(v,0,u))%yh;
            else tmp=(tmp*1ll*(DP(v,0,u)+DP(v,1,u)))%yh;
        }else{
            ll sum=1;
            if(c[v]==1) sum=(sum*1ll*DP(v,0,u))%yh;
            else sum=(sum*1ll*DP(v,1,u))%yh;    
                
            for(int j=head[u];j;j=e[j].nex){
                int tv=e[j].to;
                if(tv==v||tv==fa) continue;
                if(c[tv]==1) sum=(sum*1ll*DP(tv,0,u))%yh;
                else sum=(sum*1ll*(DP(tv,0,u)+DP(tv,1,u)))%yh;
            }
            tmp=(tmp+sum)%yh;       
        }
    }   
    return tmp%yh;  
}
 
int main(){
    n=read();
    for(int i=1;i<=n;++i) c[i]=read(),cnt+=c[i];
    for(int i=1;i<n;++i){
        int u=read(),v=read();
        in[u]++,in[v]++;
        Link(u,v);
        Link(v,u);
    }
    
    if(in[1]==n-1){
        printf("%d\n",(c[1])?1:cnt);
        return 0;
    }
    
    memset(f,-1,sizeof(f));
    Ans=(c[1]==1)?DP(1,0,0):DP(1,1,0);
    printf("%lld\n",Ans);
    return 0;
}