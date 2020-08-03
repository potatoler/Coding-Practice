#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200005;
int n,len,f[maxn];
struct Friendly{
	int nth,sth;
}fc[maxn];
bool cmp(Friendly x,Friendly y){
	return x.nth<y.nth;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&fc[i].nth,&fc[i].sth);
	sort(fc+1,fc+1+n,cmp);
	f[++len]=fc[1].sth;
	for(int i=2;i<=n;i++){
		int p=upper_bound(f+1,f+len+1,fc[i].sth)-f;
		f[p]=fc[i].sth;
		if(p>len) len++;
	}
	printf("%d\n",len);
	return 0;
}