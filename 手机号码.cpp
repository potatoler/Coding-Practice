#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
typedef long long ll;
ll l, r, digit[15];
ll f[15][10][10][2][2][2];
// current position, very last number, second last number, if trible-numbers exit, if 8 exits, if 4 exits;

inline ll DFS(int position, int veryLast, int secondLast, bool ifTrible, bool ifEight, bool ifFour, bool limited){
	if(ifEight && ifFour) return 0;
	if(!position) return ifTrible;
	if(!limited && f[position][veryLast][secondLast][ifTrible][ifEight][ifFour] != -1) return f[position][veryLast][secondLast][ifTrible][ifEight][ifFour];
	ll ans = 0;
	int maxDigit = limited? digit[position] : 9;
	for(int i=0;i<=maxDigit;i++)
		ans += DFS(position-1, i, veryLast, ifTrible || (i==veryLast && i==secondLast), ifEight || (i==8), ifFour || (i==4), limited && (i==maxDigit));
	if(!limited) f[position][veryLast][secondLast][ifTrible][ifEight][ifFour] = ans;
	return ans;
}

inline ll Count(ll x){
	int len = 0;
	while(x){
		digit[++len] = x % 10;
		x /= 10;
	}
	if(len != 11) return 0;
	memset(f, -1, sizeof(f));
	ll ans = 0;
	for(int i=1;i<=digit[len];i++)
		ans += DFS(len-1, i, 0, 0, i==8, i==4, i==digit[len]);
	return ans;
}

int main(){
	scanf("%lld%lld",&l,&r);
	printf("%lld", Count(r) - Count(l-1));
	return 0;
}