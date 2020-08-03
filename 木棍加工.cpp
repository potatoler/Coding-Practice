#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=5005;
struct Stick{
	int len,wth;
}s[maxn];
int n,sum,tmp;
bool vis[maxn];
bool cmp(Stick a,Stick b){
	if(a.len==b.len) return a.wth>b.wth;
	return a.len>b.len;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&s[i].len,&s[i].wth);
	sort(s+1,s+1+n,cmp);
	for(int i=1;i<=n;i++)
		if(vis[i]==false){
			tmp=s[i].wth;
			for(int j=i+1;j<=n;j++)
				if(s[j].wth<=tmp&&vis[j]==false) vis[j]=true,tmp=s[j].wth;
		}
	for(int i=1;i<=n;i++)
		if(vis[i]==false) sum++;
	printf("%d",sum);
}