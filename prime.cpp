#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
//#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=30000007,maxa=15000000;
int n,a[maxn],m,mx,cnt,z[maxa],f[maxn];
inline int max(int x,int y){
	return x>y? x:y;
}
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		mx=max(mx,a[i]);
		if(a[i]==1) cnt++;
	}
	for(int i=2;i<=mx*2;i++)
		f[i]=true;
	for(int i=1;i<=mx*2;i++){
		if(f[i]) z[++m]=i;
		for(int j=1;j<=m;j++){
			if(i*z[j]>mx*2) break;
			f[i*z[j]]=false;
		}
	}	
	if(cnt>2){
		int x=0;
		for(int i=1;i<=n;i++)
			if(a[i]!=1&&f[a[i]+1]) x=max(x,a[i]);
		if(x==0){
			printf("%d\n",cnt);
			for(int i=1;i<=cnt;i++)
				printf("1 ");
		}else{
			printf("%d\n",cnt+1);
			for(int i=1;i<=cnt;i++)
				printf("1 ");
			printf("%d\n",x);
		}
	}
	if(cnt==2){
		int x=0,y=0,w=0;
		for(int i=1;i<=n;i++)
			if(a[i]!=1&&f[a[i]+1]) x=max(x,a[i]);
		if(x) printf("3\n1 1 %d\n",x);
		else{
			for(int i=1;i<n;i++)
				for(int j=i+1;j<=n;j++)
					if(f[a[i]+a[j]]&&a[i]+a[j]>w){
						w=a[i]+a[j];
						x=a[i],y=a[j];
					}
			if(x>y) swap(x,y);
			printf("2\n%d %d\n",x,y);
		}
	}
	if(cnt<2){
		int x=0,y=0,w;
		for(int i=1;i<n;i++)
			for(int j=i+1;j<=n;j++)
				if(f[a[i]+a[j]]&&a[i]+a[j]>w){
					w=a[i]+a[j];
					x=a[i],y=a[j];
				}
		if(x>y) swap(x,y);
		printf("2\n%d %d\n",x,y);
	}
	return 0;
}