#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100005;
struct Shop{
	unsigned long long a,b;
}shop[maxn];
unsigned long long s,tmp,ans;
int n;
bool cmp(Shop x,Shop y){
	return x.a-x.b<y.a-y.b||(x.a-x.b==y.a-y.b&&x.a<y.a);
}
int main(){
	scanf("%d%llu",&n,&s);
	for(int i=1;i<=n;i++)
		scanf("%llu%llu",&shop[i].a,&shop[i].b);
	sort(shop+1,shop+1+n,cmp);
	for(int i=1;i<=n;i++)
		if(shop[i].a<=shop[i].b&&s>=shop[i].a){
			printf("-1\n");
			return 0;
		}
	for(int i=1;i<=n;i++)
		while(s>=shop[i].a){
			tmp=(s-shop[i].a)/(shop[i].a-shop[i].b);
			tmp++;
			ans+=tmp;
			s-=tmp*(shop[i].a-shop[i].b);
		}
	printf("%llu",ans);
	return 0;
}