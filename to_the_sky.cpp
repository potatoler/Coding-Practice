#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=1010,N=1010;
int n,m;
int f[M],a[N],b[N],c[101][20],cc[101],cn;
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        int C;
        scanf("%d%d%d",&a[i],&b[i],&C);
        cn=max(cn,C);
        cc[C]++;
        c[C][cc[C]]=i;
    }
    for(int i=1;i<=cn;i++)
        for(int j=m;j>=0;j--)
            for(int k=1;k<=cc[i];k++)
            if(j>=a[c[i][k]])
            f[j]=max(f[j],f[j-a[c[i][k]]]+b[c[i][k]]);
    printf("%d\n",f[m]);
}