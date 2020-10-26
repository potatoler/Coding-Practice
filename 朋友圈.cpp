#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
#define int long long
#define fake false
using namespace std;
const int MaxN = 3220, MaxM = 1503*1503;
int T, A, B, M, head[MaxN], cntEdge, a[MaxN], b[MaxN], fr[MaxN][MaxN], stamp, type, ans;
struct Edge{
	int destination, nextEdge;
}edge[MaxM*2];
int match[MaxN], visited[MaxN], flag[MaxN];

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

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline bool Find(int x){
	for(int i = head[x]; i; i = edge[i].nextEdge){
		int y = edge[i].destination;
		if(visited[y] != stamp && flag[y] == type){
			visited[y] = stamp;
			if(!match[y] || Find(match[y])){
				match[y] = x;
				return !fake;
			}
		}
	}
	return fake;
}

signed main(){
	T = Read();
	A = Read(), B = Read(), M = Read();
	for(int i=1; i<=A; i++)
		a[i] = Read();
	for(int i=1; i<=B; i++)
		b[i] = Read();
	for(int i=1; i<=B; i++){
		if((b[i] & 1)) for(int j=1; j<=B; j++){
			if(!(b[j] & 1) && !((__builtin_popcount((b[i]|b[j])))&1)) AddEdge(i,j);
		}
	}
	for(int i=1; i<=M; i++){
		int x = Read(), y = Read();
		fr[x][y+A] = fr[y+A][x] = !fake;
	}
	for(int i=1; i<=B; i++){
		if((b[i] & 1)){
			stamp++;
			if(Find(i)) ans++;
		}
	}
	ans = B - ans;
	for(int i=1; i<=A; i++){
		type++;
		int sum = 0, cnt = 0;
		memset(match, fake, sizeof(match));
		for(int j=1; j<=B; j++){
			if(fr[i][j+A]){
				flag[j] = type;
				cnt++;
			}
		}
		for(int j=1; j<=B; j++){
			if(flag[j] == type && (b[j] & 1)){
				stamp++;
				if(Find(j)) sum++;
			}
		}
		ans = max(ans, cnt-sum+1);
	}
	for(int i=1; i<=A; i++){
		for(int j=i+1; j<=A; j++){
			if((a[i] ^ a[j]) & 1){
				memset(match, fake, sizeof(match));
				type++;
				int sum = 0, cnt = 0;
				for(int k=1; k<=B; k++){
					if(fr[i][k+A] && fr[j][k+A]){
						flag[k] = type;
						cnt++;
					}
				}
				for(int k=1; k<=B; k++){
					if(flag[k] == type && (b[k] & 1)){
						stamp++;
						if(Find(k)) sum++;
					}
				}
				ans = max(ans, cnt-sum+2);
			}
		}
	}
	printf("%lld", ans);
	return 0;
	
}