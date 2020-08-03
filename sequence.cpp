#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,m,T;
bool fl;
long long a[maxn],b[maxn];
int t[maxn],u[maxn],v[maxn];
void dfs(){
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i]) break;
		if(i==n){
			fl=1;
			return;
		}
	}
	for(int i=1;i<=m;i++){
		if(t[i]==1){
			a[u[i]]++;a[v[i]]++;
			dfs();
			a[u[i]]--;a[v[i]]--;

			a[u[i]]--;a[v[i]]--;
			dfs();
			a[u[i]]++;a[v[i]]++;
		}
		if(t[i]==2){
			a[u[i]]++;a[v[i]]--;
			dfs();
			a[u[i]]--;a[v[i]]++;

			a[u[i]]--;a[v[i]]++;
			dfs();
			a[u[i]]++;a[v[i]]--;
		}
	}
	return;
}
int main(){
	freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		fl=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%lld",&b[i]);
		for(int i=1;i<=m;i++)
			scanf("%d%d%d",&t[i],&u[i],&v[i]);
		dfs();
		cout<<fl<<endl;
	}
}