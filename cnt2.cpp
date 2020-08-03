#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2005;
int n;
char s[maxn];
bitset<maxn>f[maxn];
int main(){
    LL sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("\n%s",s+1);
        for(int j=1;j<=n;++j)
            if(s[j]=='1') f[i][j]=1;
        f[i][i]=1;
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j){
            if(f[j][i]) f[j]|=f[i];
        }
    for(int i=1;i<=n;++i) sum+=f[i].count(); 
    printf("%lld",sum);
}