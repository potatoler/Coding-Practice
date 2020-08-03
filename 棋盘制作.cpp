#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 2005;
int n, m, cur, square, rectangle, stack[MaxN], top, board[MaxN][MaxN], len[MaxN];
#define a min((len[stack[top]]), (cur-stack[top-1]-1))
#define b max((len[stack[top]]), (cur-stack[top-1]-1))

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&board[i][j]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			if(i>1 && board[i][j] != board[i-1][j]) ++len[j];
			else len[j] = 1;
		cur = 1;
		while(cur <= m){
			stack[0] = cur-1;
			top = 1;
			stack[top] = cur++;
			while(cur <= m && (board[i][cur] != board[i][cur-1])){
				while(top && len[stack[top]] > len[cur]){
					square = max(square, a*a);
					rectangle = max(rectangle, a*b);
					--top;
				}
				stack[++top] = cur++;
			}
			while(top){
				square = max(square, a*a);
				rectangle = max(rectangle, a*b);
				--top;
			}
		}
	}
	printf("%d\n%d\n", square, rectangle);		
	return 0;
}