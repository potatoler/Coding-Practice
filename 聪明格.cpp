#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 11;
int n, a[MaxN][MaxN], cntSolution, nextStep[4][2], mul[MaxN*MaxN], cntBlock, belong[MaxN][MaxN], factor[MaxN*MaxN][MaxN], blockSize[MaxN*MaxN], cntFactor[MaxN][MaxN][MaxN], cntAvailable, locate[MaxN*MaxN][2], ans[MaxN][MaxN], clipboard[MaxN][MaxN];
bool limitedLine[MaxN][MaxN], limitedColumn[MaxN][MaxN];

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
	nextStep[0][0] = 1;
	nextStep[0][1] = 0;
	nextStep[1][0] = -1;
	nextStep[1][1] = 0;
	nextStep[2][0] = 0;
	nextStep[2][1] = 1;
	nextStep[3][0] = 0;
	nextStep[3][1] = -1;
	return;
}

inline void FindtheBlocks(int x, int y){
	belong[x][y] = cntBlock;
	blockSize[cntBlock]++;
	for(int i=0; i<4; i++){
		int nx = x + nextStep[i][0], ny = y + nextStep[i][1];
		if(a[nx][ny] == a[x][y] && !belong[nx][ny]) FindtheBlocks(nx, ny);
	}
	return;
}

inline bool CheckMul(){
	for(int i=1; i<=cntBlock; i++)
		if(mul[i] != 1) return false;
	return true;
}

inline void Paste(){
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			ans[i][j] = clipboard[i][j];
	return;
}

inline void Choose(){
	int better = 2;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(ans[i][j] < clipboard[i][j]){
				better = 0;
				break;
			}
			else if(ans[i][j] > clipboard[i][j]){
				better = 1;
				break;
			}
		}
		if(better != 2) break;
	}
	if(better) Paste();
	return;
}

inline void FillNumbers(int x){
	if(x == cntAvailable+1){
		cntSolution++;
		if(!CheckMul()) return;
		if(cntSolution == 1) Paste();
		else Choose();
		return;
	}
	int nx = locate[x][0], ny = locate[x][1], tmp = belong[nx][ny];
	if(blockSize[tmp] == 1){
		int value = mul[tmp];
		if(value <= n && value >= 1 && !limitedLine[nx][value] && !limitedColumn[ny][value]){
			limitedLine[nx][value] = true;
			limitedColumn[ny][value] = true;
			mul[tmp] = 1;
			clipboard[nx][ny] = value;
			FillNumbers(x+1);
			limitedLine[nx][value] = false;
			limitedColumn[ny][value] = false;
			mul[tmp] = value;
		}
	}
	else{
		for(int i=1; i<=n; i++){
			if(factor[tmp][i] && !limitedLine[nx][i] && !limitedColumn[ny][i] && mul[tmp] % i == 0){
				mul[tmp] /= i;
				limitedLine[nx][i] = true;
				limitedColumn[ny][i] = true;
				clipboard[nx][ny] = i;
				blockSize[tmp]--;
				FillNumbers(x+1);
				mul[tmp] *= i;
				limitedLine[nx][i] = false;
				limitedColumn[ny][i] = false;
				blockSize[tmp]++;
			}
		}
	}
	return;
}

signed main(){
	Init();
	n = Read();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++){
			cntAvailable++;
			locate[cntAvailable][0] = i;
			locate[cntAvailable][1] = j;
			a[i][j] = Read();
		}
						
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(!belong[i][j]){
				cntBlock++;
				mul[cntBlock] = a[i][j];
				factor[cntBlock][1] = n * n;
				for(int k=2; k<=n; k++){
					if(a[i][j] % k == 0){
						int tms = 1;
						for(int l=k; a[i][j] % l == 0; l*=k)
							tms++;
						factor[cntBlock][k] = tms;
					}
					else factor[cntBlock][k] = 0;
				}
				FindtheBlocks(i,j);
			}
		}
	}
	
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++)
				cntFactor[i][j][k] = factor[belong[i][j]][k];
		}
	}
	
	//IMPORTANT PART
	for(int i=1; i<=cntAvailable; i++){
		for(int j=i+1; j<=cntAvailable; j++){
			if(a[locate[i][0]][locate[i][1]] > a[locate[j][0]][locate[j][1]]){
				swap(locate[i][0], locate[j][0]);
				swap(locate[i][1], locate[j][1]);
			}
		}
	}
	
	FillNumbers(1);
	
	printf("%lld\n", cntSolution);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			printf("%lld ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}