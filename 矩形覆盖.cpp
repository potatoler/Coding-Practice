#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 55;
int n, k, ans = INT_MAX;
struct Vertex{
	int x, y;
}vertex[MaxN];
struct Matrix{
	int left, right, top, bottom;
	bool flag;
}matrix[5];

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

inline bool In(Matrix a, int x, int y){
	if(x >= a.left && x <= a.right && y >= a.bottom && y <= a.top) return true;
	return false;
}

inline bool Judge(Matrix a, Matrix b){
	if(In(a, b.left, b.top)) return true;
	if(In(a, b.left, b.bottom)) return true;
	if(In(a, b.right, b.top)) return true;
	if(In(a, b.right, b.bottom)) return true;
	return false;
}

inline void DFS(int num){
	int value = 0;
	for(int i=1; i<=k; i++){
		if(matrix[i].flag){
			for(int j=i+1; j<=k; j++)
				if(matrix[i].flag && Judge(matrix[i], matrix[j])) return;
		}
		value += (matrix[i].right - matrix[i].left) * (matrix[i].top - matrix[i].bottom);
	}
	if(value >= ans) return;
	if(num > n){
		ans = value;
		return;
	}
	for(int i=1; i<=k; i++){
		Matrix memory = matrix[i];
		if(!matrix[i].flag){
			matrix[i].flag = true;
			matrix[i].left = matrix[i].right = vertex[num].x;
			matrix[i].top = matrix[i].bottom = vertex[num].y;
			DFS(num+1);
			matrix[i] = memory;
			break;
		}
		else{
			matrix[i].right = max(matrix[i].right, vertex[num].x);
			matrix[i].left = min(matrix[i].left, vertex[num].x);
			matrix[i].bottom = min(matrix[i].bottom, vertex[num].y);
			matrix[i].top = max(matrix[i].top, vertex[num].y);
			DFS(num+1);
			matrix[i] = memory;
		}
	}
}

signed main(){
	n = Read(), k = Read();
	for(int i=1; i<=n; i++)
		vertex[i].x = Read(), vertex[i].y = Read();
	DFS(1);
	printf("%lld", ans);
	return 0;
}