#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=2005;
int f[maxn][maxn],lena,lenb;
char a[maxn],b[maxn];
int main(){
	scanf("%s%s",a,b);
	lena=strlen(a),lenb=strlen(b);
	for(int i=1;i<=lena;i++)
		f[i][0]=i;
	for(int i=1;i<=lenb;i++)
		f[0][i]=i;
	for(int i=1;i<=lena;i++)
		for(int j=1;j<=lenb;j++){
			if(a[i-1]==b[j-1]){
				f[i][j]=f[i-1][j-1];
				continue;
			}
			f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1;
		}
	printf("%d\n",f[lena][lenb]);
}