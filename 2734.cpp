#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MaxN = 100005, Mod = 1000000001;
typedef long long ll;
bool vis[MaxN];
int n, a[20][20], line[20], f[20][MaxN];
ll ans = 1;
ll Cal(int x){
	a[1][1] = x;
	int column;
	for(int i=1;i;i++){
		if(i != 1){
			a[i][1] = a[i-1][1] * 2;
			if(a[i][1] > n){
				column = i-1;
				break;
			}
		}
		vis[a[i][1]] = true;
		for(int j=2;j;j++){
			a[i][j] = a[i][j-1] * 3;
			if(a[i][j] > n){
				line[i] = j-1;
				break;
			}
			vis[a[i][j]] = true;
		}
	}
	line[0] = 1;
	for(int i=0;i<=column;i++)
		for(int j=0; j < (1<<line[i]); j++)
			f[i][j]=0;
	line[column+1] = 0, f[column+1][0] = 0;
	f[0][0] = 1;
	for(int i=0;i<=column;i++){
		for(int j=0; j < (1<<line[i]); j++){
			if(f[i][j]){
				if(j & (j>>1)) continue;
				for(int k=0; k < (1<<line[i+1]); k++){
					if(j & k)continue;
					f[i+1][k] = (f[i+1][k] + f[i][j]) % Mod;
				}
			}
		}
	}
	return f[column+1][0];
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		if(!vis[i]) ans = (ans * Cal(i)) % Mod;
	printf("%lld\n",ans);
	return 0;
}