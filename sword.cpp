#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=5505;
int n,m,s;
long long a[maxn],f[maxn][maxn],q[maxn],pos[maxn];
int main(){
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	memset(f,0x80,sizeof(f));
	long long ans=f[0][0];
	f[0][0]=0;
	// for(int i=1;i<=n;i++)
	// 	for(int j=m;j;j--)
	// 		for(int k=min(m,j+s-1);k>=j-1;k--)
	// 			f[i][j]=max(f[i][j],f[i-1][k]+j*a[i]);
	for(int i=1;i<=n;i++){
        int l=1,r=1;
        q[l]=f[i-1][m];
        pos[l]=m;
        for(int j=m;j;j--){
            while(pos[l]>j+s-1&&l<=r) l++;
            while(q[r]<f[i-1][j-1]&&l<=r) r--;
            pos[++r]=j-1;
            q[r]=f[i-1][j-1];
            f[i][j]=q[l]+j*a[i];
        }
    }
	for(int i=0;i<=m;i++)
		ans=max(ans,f[n][i]);
	printf("%lld\n",ans);
	return 0;
}