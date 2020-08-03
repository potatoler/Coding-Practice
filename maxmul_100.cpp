#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int maxn=50;
int n,k,a[maxn];
char s[maxn];
struct Suji{
	int len,c[maxn];
	bool sz;
};
Suji f[maxn][10],ans[50];
Suji getnum(int l,int r){
	Suji tmp;
	tmp.len=r-l+1;
	tmp.sz=true;
	for(int i=1;i<=tmp.len;i++)
		tmp.c[i]=a[r-i+1];
	return tmp;
}
Suji mul(Suji m1,Suji m2){
	Suji res;
	res.sz=true;
	res.len=m1.len+m2.len-1;
	for(int i=1;i<=res.len;i++)
		res.c[i]=0;
	for(int i=1;i<=m1.len;i++)
		for(int j=1;j<=m2.len;j++)
			res.c[i+j-1]+=m1.c[i]*m2.c[j];
	int q=0;
	for(int i=1;i<=res.len;i++){
		res.c[i]+=q;
		q=res.c[i]/10;
		res.c[i]%=10;
	}
	while(q){
		res.c[++res.len]=q%10;
		q/=10;
	}
	return res;
}
Suji mx(Suji m1,Suji m2){
	if(!m1.sz||m1.len<m2.len) return m2;
	if(!m2.sz||m2.len<m1.len) return m1;
	for(int i=m1.len;i;i--){
		if(m1.c[i]>m2.c[i]) return m1;
		else if(m2.c[i]>m1.c[i]) return m2;
	}
	return m1;
}
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",s);
	for(int i=0;i<n;i++)
		a[i+1]=s[i]-'0';
	for(int i=1;i<=n;i++){
		ans[i].sz=false;
		for(int j=1;j<=k;j++)
			f[i][j].sz=false;
	}
	for(int i=1;i<=n;i++){
		f[i][1]=getnum(1,i);
		for(int j=2;j<=k;j++){
			for(int l=j-1;l<i;l++){
				if(f[l][j-1].sz) f[i][j]=mx(f[i][j],mul(f[l][j-1],getnum(l+1,i)));
			}
		}
		if(f[i][k].sz) ans[i]=mul(f[i][k],getnum(i+1,n));
	}
	Suji lst;
	lst.sz=false;
	for(int i=1;i<=n;i++){
		Suji tmp=mx(ans[i],lst);
		lst=tmp;
	}
	for(int i=lst.len;i;i--)
		printf("%d",lst.c[i]);
	return 0;
}