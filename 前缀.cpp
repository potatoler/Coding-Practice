#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
#define fake false
using namespace std;
const int MaxN = 100005, Mod = 998244353;
char s[MaxN], t[MaxN];
int slen, n, pos[30][MaxN], tot[MaxN], idx[MaxN][30];

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

inline int QuickPower(int x, int y){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return res;
}

inline int Serial(char ch){
	return ch-'a';
}

inline bool Check(){
	int tlen = strlen(t+1);
	for(int i=1; i<=tlen; i++){
		if(t[i] != '*' && !isdigit(t[i]) && !tot[Serial(t[i])]) return fake;
	}
	return !fake;
}

signed main(){
	scanf("%s", s+1);
	slen = strlen(s+1);
	s[slen+1] = s[1];
	for(int i=1; i<=slen; i++){
		tot[Serial(s[i])]++;
		memcpy(idx[i], idx[i-1], sizeof(idx[i-1]));
		pos[Serial(s[i])][++pos[Serial(s[i])][0]] = i;
		idx[i][Serial(s[i])]++;
	}
	n = Read();
	while(n--){
		scanf("%s", t+1);
		if(!Check()){
			printf("-1\n");
			continue;
		}
		int ans = 0, last = 1, tlen = strlen(t+1);
		for(int i=1; i<=tlen; i++){
			char cur = t[i];
			int once = (t[i] == '*') ? (slen) : (tot[Serial(t[i])]);
			int turn = 0, need = 0;
			if(isdigit(t[i+1])){
				while(isdigit(t[i+1])){
					turn = ((turn<<3) + (turn<<1)) % Mod;
					need = ((need<<3) + (need<<1) + t[++i] - 48) % Mod;
					turn = (turn + need/once) % Mod;
					need %= once;
				}
			}
			else need = 1;
			if(cur == '*') need += once - (slen-last+1);
			else need += once - (tot[Serial(cur)] - idx[last-1][Serial(cur)]);
			if(need > once){
				need -= once;
				turn++;
			}
			if(turn == 0) turn = Mod;
			if(need == 0){
				need += once;
				turn--;
			}
			if(cur != '*'){
				ans += pos[Serial(cur)][need] - last + 1;
				last = pos[Serial(cur)][need] % slen + 1;
			}
			else{
				ans += need - last + 1;
				last = need % slen + 1;
			}
			ans = (ans + (slen*turn % Mod)) % Mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}