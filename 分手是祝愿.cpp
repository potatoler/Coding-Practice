#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
const int MaxN = 100005, Mod = 100003;
int n, k, l[MaxN];
long long f[MaxN], inv[MaxN], ans, ori;

void CalInv(){
	inv[1] = 1;
	for(int i=2;i<=n;i++)
		inv[i] = ((Mod - Mod/i) * inv[Mod%i]) % Mod;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&l[i]);
	CalInv();
	for(int i=n;i>=1;i--){
		if(!l[i]) continue;
		ori++;
		for(int j=1;j*j<=(i);j++){
			if(i%j == 0){
				l[j] ^= 1;
				if(i/j != j) l[i/j] ^= 1;
			}
		}
	}
	//f[n] = 1;
	for(int i=n;i>k;i--)
		f[i] = ((n-i) * f[i+1] % Mod + n) % Mod * inv[i] % Mod;
	for(int i = k+1;i<=ori;i++) ans = (ans + f[i]) % Mod;
	if(ori <= k) ans = ori % Mod;
	else ans += k % Mod;
	for(int i=1;i<=n;i++)
		ans = (ans * i) % Mod;
	printf("%lld", ans);
	return 0;
}