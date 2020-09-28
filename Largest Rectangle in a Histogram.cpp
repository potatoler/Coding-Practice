#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, stack[MaxN], top, ans;
struct Rectangle{
	int height, lSon, rSon, subtreeSize;
	inline void Clear(){
		height = lSon = rSon = subtreeSize = 0;
		return;
	}
}rec[MaxN];

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


inline void Reset(){
	for(int i=0; i<MaxN; i++)
		rec[i].Clear();
	memset(stack, 0, sizeof(stack));
	top = ans = 0;
	return;
}

inline void Build(int n){
	for(int i=1; i<=n; i++){
		int pos = top;
		rec[i].height = Read();
		while(pos && rec[stack[pos]].height >= rec[i].height)
			pos--;
		if(pos) rec[stack[pos]].rSon = i;
		if(pos < top) rec[i].lSon = stack[pos+1];
		stack[++pos] = i;
		top = pos;
	}
	return;
}

inline void DFS(int x){
	if(rec[x].lSon) DFS(rec[x].lSon);
	if(rec[x].rSon) DFS(rec[x].rSon);
	rec[x].subtreeSize = rec[rec[x].lSon].subtreeSize + rec[rec[x].rSon].subtreeSize + 1;
	ans = max(ans, rec[x].height * rec[x].subtreeSize);
	return;
}

signed main(){
	while(scanf("%lld", &n) != EOF && n){
		Reset();
		Build(n);
		DFS(stack[1]);
		printf("%lld\n", ans);
	}
	return 0;
}