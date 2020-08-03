#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
int n, mod, t[20];
struct Matrix{
	int number[3][3];
	
	inline void printMatrix(){
		for(int i=0;i<3;i++){
			printf("	");
			for(int j=0;j<3;j++)
				printf("%lld ", number[i][j]);
			printf("\n");
		}
	}
	
}ori, ans;

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
	return num;
}

inline Matrix operator * (Matrix a, Matrix b){
	Matrix res;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			res.number[i][j] = 0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				res.number[i][j] = (res.number[i][j] + a.number[i][k] * b.number[k][j] % mod) % mod;
	return res;
}

inline Matrix QuickPower(Matrix x, int y){
	if(y == 1) return x;
	Matrix res = QuickPower(x, y/2);
	res = res * res;
	if(y & 1) res = res * x;
	return res;
}

signed main(){
	n = Read(), mod = Read();
	ans.number[0][1] = ans.number[0][2] = ori.number[1][0] = ori.number[1][1] = ori.number[2][1] = ori.number[2][2] = 1;
	t[0] = 1;
	for(int i=1;i<=18;i++)
		t[i] = t[i-1] * 10;
//	for(int i=1;i<=18;i++)
//		printf("%lld ", t[i]);
//	printf("\n");
	for(int i=1; ;i++){
		ori.number[0][0] = t[i] % mod;
		int tmp = min(n, t[i] - 1) - t[i-1] + 1;
		ans = ans * QuickPower(ori, tmp);
		if(t[i] - 1 >= n) break;
//		printf("Round %lld:\n", i);
//		printf("	ans:\n"), ans.printMatrix();
//		printf("	ori:\n"), ori.printMatrix();
	}
	printf("%lld\n", ans.number[0][0]);
	return 0;
}