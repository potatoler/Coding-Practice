#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int unsigned long long
const int Mod = 10000007;
int number, length, digit[55], f[55][55][55];
//f[i][j][k]: the number of numbers, which their first i digits have j ones and there are k ones in total

inline int QuickPower(int x, int y){
	int ans = 1;
	while(y){
		if(y & 1) ans = ans * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return ans % Mod;
}

inline int DFS(int pos, int cnt, int sum, bool limited){
	if(!pos) return cnt == sum;
	if(!limited && f[pos][cnt][sum] != -1) return f[pos][cnt][sum];
	int ans = 0, up = limited? digit[pos] : 1;
	for(int i = 0; i <= up; i++)
		ans += DFS(pos-1, cnt + (i==1), sum, limited && (i==digit[pos]));
	if(!limited) f[pos][cnt][sum] = ans;
	return ans;
}

signed main(){
	scanf("%llu", &number);
	while(number){
		digit[++length] = number & 1;
		number >>= 1;
	}
//	for(int i = 1; i <= length; i++)
//		printf("%lld ", digit[i]);
//	printf("\n");
	int ans = 1;
	for(int i = 1; i <= length; i++){
		memset(f, -1, sizeof(f));
		ans = ans * QuickPower(i, DFS(length, 0, i, true)) % Mod;
	}
	printf("%llu", ans);
}