#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
struct Index{
	int rank, sum;
}cntZero[10];
int a[10][10], line[10][10], column[10][10], circle[10][10], s[100][4], u, OK, most = -1, have;

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

inline int GetCircle(int x, int y){
	if(x <= 3){
		if(y <= 3) return 1;
		else if(y <= 6) return 2;
		else return 3;
	}
	else if(x <= 6){
		if(y <= 3) return 4;
		else if(y <= 6) return 5;
		else return 6;
	}
	else{
		if(y <= 3) return 7;
		else if(y <= 6) return 8;
		else return 9;
	}
}

inline int GetPoint(int x, int y){
	if(x == 1 || y == 1 || x == 9 || y == 9) return 6;
	if(x == 2 || y == 2 || x == 8 || y == 8) return 7;
	if(x == 3 || y == 3 || x == 7 || y == 7) return 8;
	if(x == 4 || y == 4 || x == 6 || y == 6) return 9;
	return 10;
}

inline void DFS(int p, int score){
	if(p == u){
		if(score > most) most = score;
		return;
	}
	for(int i=1; i<=9; i++){
		if(!line[s[p][0]][i] && !column[s[p][1]][i] && !circle[s[p][3]][i]){
			line[s[p][0]][i] = column[s[p][1]][i] = circle[s[p][3]][i] = 1;
			DFS(p+1, score+(s[p][2]*i));
			line[s[p][0]][i] = column[s[p][1]][i] = circle[s[p][3]][i] = 0;
		}
	}
	return;
}

inline bool cmp(Index a, Index b){
	return a.sum < b.sum;
}

signed main(){
	for(int i=1; i<=9; i++)
		cntZero[i].rank = i;
	for(int i=1; i<=9; i++)
		for(int j=1; j<=9; j++){
			a[i][j] = Read();
			if(a[i][j] > 0) line[i][a[i][j]] = column[j][a[i][j]] = circle[GetCircle(i,j)][a[i][j]] = 1, have += a[i][j] * GetPoint(i,j);
			else cntZero[i].sum++;
		}
	sort(cntZero+1, cntZero+10, cmp);
	for(int i=1; i<=9; i++){
		for(int j=1; j<=9; j++){
			if(a[cntZero[i].rank][j] == 0){
				s[u][0] = cntZero[i].rank;
				s[u][1] = j;
				s[u][2] = GetPoint(cntZero[i].rank, j);
				s[u][3] = GetCircle(cntZero[i].rank, j);
				u++;
			}
		}
	}
	DFS(0, have);
	printf("%lld", most);
	return 0;
}