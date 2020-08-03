#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=100005;
int n,m;
double k,ans,val[maxn],f[maxn];
deque<int> q;
int main(){
	scanf("%d%d%lf",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%lf",&val[i]);
	for(int i=n;i;i--){
		f[i]=val[i];
		while(!q.empty()){
			if(i+m<q.front()) q.pop_front();
			else break;
		}
		if(!q.empty()) f[i]=max(f[i],f[q.front()]*k+val[i]);
		while(!q.empty()){
			if(f[q.back()]<f[i]) q.pop_back();
			else break;
		}
		q.push_back(i);
		if(i<=m) ans=max(ans,f[i]);
	}
	printf("%.2lf\n",ans);
	return 0;
}