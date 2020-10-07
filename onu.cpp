#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, c, v, ans[MaxN], candy;
struct Card{
	int serial, score, type;
};
vector<Card> D[MaxN], C[MaxN];

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

inline bool cmp(const Card &a, const Card &b){
	return a.score > b.score;
}

signed main(){
	n = Read(), m = Read(), c = Read(), v = Read();
	candy = v;
	for(int i=1; i<=n; i++){
		int type = Read(), score = Read();
		Card thisCard = (Card){i,score,type};
		D[type].push_back(thisCard);
	}
	for(int i=1; i<=m; i++){
		int type = Read(), score = Read();
		Card thisCard = (Card){i,score,type};
		C[type].push_back(thisCard);
	}
	for(int i=1; i<MaxN; i++){
		sort(D[i].begin(), D[i].end(), cmp);
		sort(C[i].begin(), C[i].end(), cmp);
	}
	for(int i=1; i<MaxN; i++){
		int pd = 0;
		for(int pc = 0; pc < C[i].size(); pc++){
			if(pd >= D[i].size() || C[i][pc].score > D[i][pd].score){
				ans[C[i][pc].serial] = -1;
				candy -= c;
			}
			else {
				candy += c + D[i][pd].score;
				ans[C[i][pc].serial] = D[i][pd].serial;
				pd++;
			}
		}
		for(int pc = 0; pc < C[i].size(); pc++){
			if(pd < D[i].size() && ans[C[i][pc].serial] == -1){
				candy += D[i][pd].score;
				ans[C[i][pc].serial] = D[i][pd].serial;
				pd++;
			}
		}
	}
	printf("%lld\n", candy);
	for(int i=1; i<=m; i++)
		printf("%lld\n", ans[i]);
}