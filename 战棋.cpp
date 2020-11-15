#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 55;
int n, xx, AA, BB, CC, ans1, ans2;
int attack[2][MaxN], health[2][MaxN], race[2][MaxN], type[2][MaxN];
struct Chess{
	int attack, health, race, type;
};

class Player{
	public:
	Chess chess[MaxN];
	int cnt, leader, captain;
	
	inline void Init(int p){
		cnt = n;
		leader = captain = 0;
		for(int i=0; i<cnt; i++){
			chess[i].attack = attack[p][i];
			chess[i].health = health[p][i];
			chess[i].race = race[p][i];
			chess[i].type = type[p][i];
			if(chess[i].type == 2) leader++;
			else if(chess[i].type == 4) captain++;
		}
	}
	
	inline void PreAttack(int x){
		if(chess[x].race == 0) return;
		if(captain > 0){
			chess[x].attack += 20 * (chess[x].type == 4? (captain-1) : captain);
			chess[x].health += 20 * (chess[x].type == 4? (captain-1) : captain);
		}
		return;
	}
	
	inline int Attack(int x){
		int res = chess[x].attack;
		if(leader > 0){
			if(chess[x].race == 0) res += 20 * (chess[x].type == 2? (leader-1) : leader);
		}
		return res;
	}
	
	inline void Die(int x){
		cnt--;
		int tmp = 0, f=0;
		if(chess[x].type == 2) leader--;
		if(chess[x].type == 3) tmp = 20;
		if(chess[x].type == 4) captain--;
		if(chess[x].race == 1) f = 1;
		for(int i=0; i<x; i++){
			if(chess[i].race == 0){
				chess[i].attack += tmp;
				chess[i].health += tmp;
			}
			if(chess[i].type == 5){
				chess[i].attack += 50 * f;
			}
		}
		for(int i=x; i<cnt; i++){
			chess[i] = chess[i+1];
			if(chess[i].race == 0){
				chess[i].attack += tmp;
				chess[i].health += tmp;
			}
			if(chess[i].type == 5){
				chess[i].attack += 50 * f;
			}
		}
	}
}p1, p2;

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

inline int GetID(){
	return xx = (xx * AA + BB) % CC;
}

inline void Debug(){
//	p1.Init(0), p2.Init(1);
	printf("p1:\n");
	for(int i=0; i<p1.cnt; i++){
		printf("%lld %lld %lld %lld\n", p1.chess[i].attack, p1.chess[i].health, p1.chess[i].race, p1.chess[i].type);
	}
	printf("%lld leader, %lld captain\n", p1.leader, p1.captain);
	printf("\n");
	printf("p2:\n");
	for(int i=0; i<p2.cnt; i++){
		printf("%lld %lld %lld %lld\n", p2.chess[i].attack, p2.chess[i].health, p2.chess[i].race, p2.chess[i].type);
	}
	printf("%lld leader, %lld captain\n", p2.leader, p2.captain);
	printf("\n");
	return;
}

inline bool Turn(){
	int x = GetID(), y = GetID();
	x = x % p1.cnt, y = y % p2.cnt;
//	printf("%lld and %lld:\n", x, y);
	p1.PreAttack(x), p2.PreAttack(y);
//	printf("before attack:\n");
//	Debug();
//	printf("\n");
	p1.chess[x].health -= p2.Attack(y);
	p2.chess[y].health -= p1.Attack(x);
	if(p1.chess[x].health <= 0) p1.Die(x);
	if(p2.chess[y].health <= 0) p2.Die(y);
//	printf("after this Round:\n");
//	Debug();
//	printf("\n");
	if(p1.cnt == 0 || p2.cnt == 0) return true;
	else return false;
}

inline void Game(){
	p1.Init(0), p2.Init(1);
//	Debug();
	while(true){
		if(Turn()){
			ans1 += p1.cnt, ans2 += p2.cnt;
			break;
		}
	}
	return;
}

signed main(){
	n = Read(), xx = Read(), AA = Read(), BB = Read(), CC = Read();
	for(int p=0; p<=1; p++){
		for(int i=0; i<n; i++){
			attack[p][i] = Read();
			health[p][i] = Read();
			char op[5];
			scanf("%s", op);
			if(op[0] == 'M') race[p][i] = 0;
			else race[p][i] = 1;
			scanf("%s", op);
			switch(op[0]){
				case 'B': {type[p][i] = 1; break;}
				case 'L': {type[p][i] = 2; break;}
				case 'K': {type[p][i] = 3; break;}
				case 'C': {type[p][i] = 4; break;}
				case 'G': {type[p][i] = 5; break;}
			}
		}
	}
	int T = 500;
	while(T--){
		Game();
	}
	printf("%lld %lld", ans1, ans2);
	return 0;
}