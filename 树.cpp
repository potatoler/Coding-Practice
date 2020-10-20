#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define ull unsigned long long
using namespace std;
const int MaxN = 1000007;
const ull Base = 793999, Mod = 1000007;
int m, n, a, b, ans, head[MaxN], cntEdge, SN[MaxN], serial;
ull xorsum[MaxN*2], hashval[MaxN*2];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*2];
#define thisSon edge[i].destination

class HashTable{
	private:
		
	int head[MaxN], nxt[MaxN], tot;
	ull value[MaxN];
	
	public:
		
	inline void Add(ull x){
		int y = x % Mod;
		tot++;
		nxt[tot] = head[y];
		value[tot] = x;
		head[y] = tot;
		return;
	}
	
	inline bool Find(ull x){
		int y = x % Mod;
		for(int i = head[y]; i; i = nxt[i])
			if(value[i] == x) return true;
		return false;
	}
}hashtable;

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

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline void DFS(int x, int father, ull last){
	SN[x] = ++serial;
	xorsum[serial] = last;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father) continue;
		DFS(thisSon, x, hashval[edge[i].value]);
		xorsum[++serial] = hashval[edge[i].value];
	}
	return;
}

signed main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n = Read(), m = Read();
	hashval[0] = 1;
	hashtable.Add(0);
	for(int i=1; i<=n; i++){
		hashval[i] = hashval[i-1] * Base;
		hashtable.Add(hashval[i]);
	}
	for(int i=1; i<n; i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w), AddEdge(v, u, w);
	}
	DFS(1, 0, (ull)0);
	for(int i=2; i<=serial; i++)
		xorsum[i] ^= xorsum[i-1];
	a = Read(), b = Read();
	while(m--){
		int x = a % n + 1, y = b % n + 1;
		a = 666073 * (ull)a % 1000000007;
		b = 233 * (ull)b % 998244353;
		ans += hashtable.Find(xorsum[SN[x]] ^ xorsum[SN[y]]);
	}
	printf("%d", ans);
	return 0;
}