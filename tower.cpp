#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, head[MaxN], cntEdge, father[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Monster{
	int HP, attack, defend, gem;
}monster[MaxN];
#define knight monster[1]
int hurt[MaxN], buff[MaxN], tms[MaxN], belong[MaxN];
bool alive[MaxN], visited[MaxN];
vector<int> block[MaxN];
struct Battle{
	int serial;
	double worth;
	bool operator < (const Battle &y) const{
		return worth < y.worth;
	}
};
priority_queue<Battle> q;

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void GetFather(int x){
	for(int i=head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(y == father[x]) continue;
		father[y] = x;
		GetFather(y);
	}
	return;
}

inline int Find(int x){
	if(belong[x] != x) belong[x] = Find(belong[x]);
	return belong[x];
}

inline void Fight(int x){
	knight.HP -= (monster[x].attack - knight.defend) * tms[x];
	knight.defend += monster[x].gem;
	return;
}

inline void FightBlock(int x){
	Fight(x);
	alive[x] = true;
	for(int i=0; i<block[x].size(); i++)
		FightBlock(block[x][i]);
	return;
}

signed main(){
//	freopen("tower.in", "r", stdin);
//	freopen("tower.out", "w", stdout);
	n = Read();
	for(int i=1; i<n; i++){
		int u = Read(), v = Read();
		AddEdge(u, v);
		AddEdge(v, u);
	}
	knight.HP = Read(), knight.attack = Read(), knight.defend = Read();
	for(int i=2; i<=n; i++){
		monster[i].HP = Read(), monster[i].attack = Read(), monster[i].defend = Read(), monster[i].gem = Read();
		hurt[i] = tms[i] = (monster[i].HP-1) / (knight.attack - monster[i].defend);
		buff[i] = monster[i].gem;
		belong[i] = i;
		q.push((Battle){i, 1.0 * buff[i] / hurt[i]});
	}
	GetFather(1);
	alive[1] = true;
	while(q.size()){
		int serial = q.top().serial, cur = Find(father[serial]);
		q.pop();
		if(visited[serial]) continue;
		visited[serial] = true;
		if(alive[father[serial]]){
			FightBlock(serial);
			continue;
		}
		hurt[cur] += hurt[serial];
		buff[cur] += buff[serial];
		block[cur].push_back(serial);
		belong[serial] = cur;
		q.push((Battle){cur, 1.0 * buff[cur] / hurt[cur]});
	}
	if(knight.HP <= 0) printf("-1");
	else printf("%lld", knight.HP);
	return 0;
}