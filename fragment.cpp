#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
int n, m, line[15], column[15];
bool visitedLine[15], visitedColumn[15], owari, okLine[15][15], okColumn[15][15];
char map[15][15], tmpi[15], tmpj[15];

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

inline void InitLine(){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			memset(tmpi, 0, sizeof(tmpi));
			memset(tmpj, 0, sizeof(tmpj));
			for(int k=1; k<=m; k++)
				tmpi[k] = map[i][k], tmpj[k] = map[j][k];
			sort(tmpi+1, tmpi+1+m);
			sort(tmpj+1, tmpj+1+m);
			okLine[i][j] = true;
			for(int k=1; k<=m; k++)
				if(tmpi[k] != tmpj[k]) okLine[i][j] = false;
		}
	}
	return;
}

inline void InitColumn(){
	for(int i=1; i<=m; i++){
		for(int j=1; j<=m; j++){
			memset(tmpi, 0, sizeof(tmpi));
			memset(tmpj, 0, sizeof(tmpj));
			for(int k=1; k<=n; k++)
				tmpi[k] = map[k][i], tmpj[k] = map[k][j];
			sort(tmpi+1, tmpi+1+n);
			sort(tmpj+1, tmpj+1+n);
			okColumn[i][j] = true;
			for(int k=1; k<=n; k++)
				if(tmpi[k] != tmpj[k]) okColumn[i][j] = false;
//			printf("%lld ", okColumn[i][j]);
		}
//		printf("\n");
	}
	return;
}

inline void Hanntei(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(map[line[i]][column[j]] != map[line[n-i+1]][column[m-j+1]]) return;
	owari = true;
	return;
}

inline void ColumnTransform(int x, int flag){
	if(owari) return;
	if(!x){
		Hanntei();
		return;
	}
	if(flag) for(int i=1; i<=m; i++){
		visitedColumn[i] = true;
		column[x] = i;
		ColumnTransform(x-1, false);
		visitedColumn[i] = false;
	}
	else for(int i=1; i<=m; i++){
		if(visitedColumn[i]) continue;
		for(int j=i+1; j<=m; j++){
			if(!visitedColumn[j] && okColumn[i][j]){
				visitedColumn[i] = visitedColumn[j] = true;
				column[x] = i;
				column[m-x+1] = j;
				ColumnTransform(x-1, false);
				visitedColumn[i] = visitedColumn[j] = false;
			}
		}
		return;
	}
}

inline void LineTransfer(int x, int flag){
	if(owari) return;
	if(!x){
		ColumnTransform((m+1)/2, m&1);
		return;
	}
	if(flag) for(int i=1; i<=n; i++){
		visitedLine[i] = true;
		line[x] = i;
		LineTransfer(x-1, false);
		visitedLine[i] = false;
	}
	else for(int i=1; i<=n; i++){
		if(visitedLine[i]) continue;
		for(int j=i+1; j<=n; j++){
			if(!visitedLine[j] && okLine[i][j]){
				visitedLine[i] = visitedLine[j] = true;
				line[x] = i;
				line[n-x+1] = j;
				LineTransfer(x-1, false);
				visitedLine[i] = visitedLine[j] = false;
			}
		}
		return;
	}
}

signed main(){
	int Num = Read(), T = Read();
	while(T--){
		n = Read(), m = Read();
		for(int i=1; i<=n; i++)
			scanf("%s", map[i]+1);
		InitLine();
		InitColumn();
//		for(int i=1; i<n; i++)
//			printf("%lld ", line[i]);
//		for(int i=1; i<m; i++)
//			printf("%lld ", column[i]);
		owari = false;
		LineTransfer((n+1)/2, n&1);
		if(owari) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}