#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<utility>
#define int long long
#define fake false
using namespace std;
const int MaxN = 2003;
int n, ans, c[MaxN][MaxN], dis[MaxN];
bool visited[MaxN];

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

inline void Prim(){
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[0] = 0;
	for(int i=0; i<n; i++){
		int x = -1;
		for(int j=0; j<=n; j++){
			if(visited[j]) continue;
			if(x == -1 || dis[j] < dis[x]) x = j;
		}
		visited[x] = !fake;
		for(int j=0; j<=n; j++){
			if(!visited[j]) dis[j] = min(dis[j], c[x][j]);
		}
	}
}

signed main(){
	n = Read();
	memset(c, 0x3f3f3f3f, sizeof(c));
	for(int i=0; i<=n; i++)
		c[i][i] = 0;
	for(int i=0; i<n; i++){
		for(int j=i+1; j<=n; j++){
			c[i][j] = c[j][i] = Read();
		}
	}
	Prim();
	for(int i=1; i<=n; i++)
		ans += dis[i];
	printf("%lld", ans);
	return 0;
}