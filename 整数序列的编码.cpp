#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 300005;
int m, b[MaxN], nxt[MaxN], lst[MaxN], cnt;
vector<int> arr[MaxN];

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

signed main(){
	m = Read();
	for(int i=1; i<=m; i++){
		b[i] = Read();
		if(b[i] == -1) cnt++;
	}
	for(int i=1; i<=cnt; i++){
		lst[i] = i-1;
		nxt[i] = i+1;
	}
	lst[1] += cnt, nxt[cnt] -= cnt;
	int p = 1;
	for(int i=1; i<=m; i++){
		if(b[i] == -1){
			nxt[lst[p]] = nxt[p];
			lst[nxt[p]] = lst[p];
		}
		else arr[p].push_back(b[i]);
		p = nxt[p];
	}
	printf("%lld\n", cnt);
	for(int i=1; i<=cnt; i++){
		printf("%lld ", (int)arr[i].size());
		for(int j=0; j<arr[i].size(); j++)
			printf("%lld ", arr[i][j]);
		printf("\n");
	}
	return 0;
}