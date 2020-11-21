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
#define lowbit(x) (x&(-x))
const int MaxN = 3003, MaxM = 12, Mod = 998244353;
using namespace std;
int n, m, S, lg[1<<MaxM], f[MaxN][1<<MaxM], son[MaxN], ans, self;

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

struct Edge{
	int destination, nextEdge;
};
class Tree{
	private:
	int head[MaxN], cntEdge;
	Edge edge[MaxN*2];
	
	public:
	int sz;
	
	inline void AddEdge(int u, int v){
		cntEdge++;
		edge[cntEdge].destination = v;
		edge[cntEdge].nextEdge = head[u];
		head[u] = cntEdge;
		return;
	}
	
	inline void Plant(){
		sz = Read();
		for(int i=1; i<sz; i++){
			int u = Read(), v = Read();
			AddEdge(u, v);
			AddEdge(v, u);
		}
		return;
	}
	
	inline void Archive(int x, int father){
		son[x] = 0;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(y == father) continue;
			Archive(y, x);
			son[x] |= (1<<(y-1));
		}
	}
	
	inline void DFS(int x, int father){
		f[x][0] = 1;
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			if(y == father) continue;
			DFS(y, x);
			for(int j=S; j>=0; j--) if(f[x][j]){
					int tmp = f[x][j];
//					printf("%lld %lld\n", tmp, j);
					for (int k = S ^ j; k; k -= lowbit(k)) {
						int pos = lg[lowbit(k)];
//						printf("%lld %lld\n", (k & -k), pos);
						if(f[y][son[pos+1]]){
							f[x][j|(1<<pos)] = (f[x][j|(1<<pos)] + tmp * f[y][son[pos+1]]) % Mod;
//							printf("%lld ", f[x][j|(1<<pos)]);
						}
				}
			}
		}
		return;
	}
}T1, T2;

inline int QuickPower(int a, int b){
	int res = 1;
	while(b){
		if(b&1) res = res * a % Mod;
		a = a * a % Mod;
		b >>= 1;
	}
	return res;
}

signed main(){
//	freopen("count.in", "r", stdin);
//	freopen("count.out", "w", stdout);
	T1.Plant();
	T2.Plant();
	S = (1<<T2.sz)-1;
//	cout<<S<<endl;
	for(int i=0; i<T2.sz; i++)
		lg[1<<i] = i;
	for(int i=1; i<=T2.sz; i++){
		memset(f, 0, sizeof(f));
		T2.Archive(i, 0);
		T1.DFS(1, 0);
		for(int j=1; j<=T1.sz; j++){
			ans = (ans + f[j][son[i]]) % Mod;
		}
	}
	T1 = T2;
	for(int i=1; i<=T2.sz; i++){
		memset(f, 0, sizeof(f));
		T2.Archive(i, 0);
		T1.DFS(1, 0);
		self = (self + f[1][son[i]]) % Mod;
	}
//	printf("%lld %lld\n", ans, self);
	printf("%lld\n", ans * QuickPower(self, Mod-2) % Mod);
	return 0;
}