#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
using namespace std;
const int Mod = 2001000097;
int power[22], digit[22];
struct Union{ int f, x, sum, cnt; };
Union record[22][202];

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

inline void Init(){
	power[0] = 1;
	for(int i=1; i<20; i++)
		power[i] = power[i-1] * 10 % Mod;
	memset(record, -1, sizeof(record));
	return;
}

inline Union DFS(int x, int sum, int limited){
	if(!x) return (Union){0,0,0,1};
	if(!limited && record[x][sum].f != -1) return record[x][sum];
	Union ans = (Union){0,0,0,0};
	for(int i=0; i<=(limited? digit[x] : 9); i++){
		int mx = limited? digit[x] : 9 ;
		Union nxt = DFS(x-1, sum+i, limited && i==mx);
		ans.x = (ans.x + nxt.x + i * power[x-1] % Mod * nxt.cnt % Mod) % Mod;
		ans.sum = (ans.sum + nxt.sum + i * nxt.cnt) % Mod;
		ans.cnt = (ans.cnt + nxt.cnt) % Mod;
		ans.f = (ans.f + i * power[x-1] * i % Mod * nxt.cnt % Mod + nxt.f + i * power[x-1] % Mod * nxt.sum % Mod + i * nxt.x % Mod) % Mod;
	}
	if(!limited) record[x][sum] = ans;
	return ans;
}

signed main(){
	freopen("hash.in", "r", stdin);
	freopen("hash.out", "w", stdout);
	Init();
	int T = Read();
	while(T--){
		int l = Read(), r = Read();
		for(int i=1; i<20; i++){
			digit[i] = r % 10;
			r /= 10;
		}
		int ans = DFS(19, 0, true).f;
		l--;
		for(int i=1; i<20; i++){
			digit[i] = l % 10;
			l /= 10;
		}
		ans = (ans - DFS(19, 0, true).f + Mod) % Mod;
		printf("%lld\n", ans);
	}
	return 0;
}