#pragma optimize(3)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005, MaxP = 32000007;
int Num, T, n, k, minFac[MaxP], prime[MaxP], cntPrime;
int cntUsed, used[64], dis[64][MaxN], cnt[64], primeFactor[64][64], pos;
bool visited[MaxN];

struct Traveller{
	int dist, home;
};
bool operator < (const Traveller &a, const Traveller &b){
	return a.dist > b.dist;
}
priority_queue <Traveller> q;

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

inline void ExGCD(int a, int b, int &x, int &y){
	if(!b){
		x = 1, y = 0;
		return;
	}
	ExGCD(b, a%b, y, x);
	y -= a / b * x;
	return;
}

inline void Init(){
	for(int i=2; i<MaxP; i++){
		if(!minFac[i]) prime[++cntPrime] = minFac[i] = i;
//		for(int j=1; j<=cntPrime && prime[j] <= minFac[i]; j++){
//			int tmp = prime[j] * i;
//			if(tmp >= MaxP) break;
//			minFac[tmp] = prime[j];
//		}
		for(int j=1; j<=cntPrime; j++){
			if(prime[j] > minFac[i] || prime[j] > MaxP/i) break;
			minFac[prime[j]*i] = prime[j];
		}
	}
	return;
}

inline void Dijkstra(){
//	while(q.size()) q.pop();
	memset(visited, false, sizeof(visited));
	for(int i=0; i < primeFactor[pos][1]; i++)
		dis[pos][i] = LLONG_MAX;
	dis[pos][0] = 0;
	q.push((Traveller){0,0});
	while(q.size()){
		while(q.size()){
			int x = q.top().home;
			if(visited[x]) q.pop();
			else break;
		}
		if(q.empty()) break;
		Traveller tmp = q.top();
		q.pop();
		for(int i=2; i<=cnt[pos]; i++){
			int to = (tmp.home + primeFactor[pos][i]) % primeFactor[pos][1];
			if(dis[pos][to] > tmp.dist + primeFactor[pos][i]){
				dis[pos][to] = tmp.dist + primeFactor[pos][i];
				q.push((Traveller){dis[pos][to], to});
			}
		}
	}
	return;
}

signed main(){
	Init();
	Num = Read(), T = Read();
	while(T--){
		n = Read(), k = Read();
		pos = 0;
		for(int i=1; i<=cntUsed; i++)
			if(used[i] == k) pos = i;
		if(!pos){
			pos = ++cntUsed;
			used[pos] = k;
			int tmp = k;
			for(int i=1; prime[i] * prime[i] <= tmp; i++){
				if(tmp % prime[i] == 0){
					primeFactor[pos][++cnt[pos]] = prime[i];
					while(tmp % prime[i] == 0) tmp /= prime[i];
				}
			}
			if(tmp != 1) primeFactor[pos][++cnt[pos]] = tmp;
			if(cnt[pos] >= 3) Dijkstra();
		}
		bool reach = false;
		for(int i=1; i<=cnt[pos]; i++){
			if(n % primeFactor[pos][i] == 0){
				reach = true;
				puts("YES");
				break;
			}
		}
		if(reach) continue;
		if(cnt[pos] <= 1){
			puts("NO");
			continue;
		}
		if(cnt[pos] == 2){
			int x = 0, y = 0;
			ExGCD(primeFactor[pos][1], primeFactor[pos][2], x, y);
			y = (y % primeFactor[pos][1] + primeFactor[pos][1]) % primeFactor[pos][1];
			int tmp = y * (n % primeFactor[pos][1]) % primeFactor[pos][1] * primeFactor[pos][2];
			if(tmp <= n) puts("YES");
			else puts("NO");
			continue;
		}
		int tmp = n % primeFactor[pos][1];
		if(dis[pos][tmp] <= n) puts("YES");
		else puts("NO");
	}
	return 0;
}