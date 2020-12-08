#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, head[MaxN], cntEdge, ind[MaxN], outd[MaxN];
int stack[MaxN], top;
struct Edge{
	int destination, nextEdge;
}edge[MaxN*10];

inline int GCD(int a, int b){
	return !b? a : GCD(b, a%b);
}

class Fraction{
	public:
	int up, down;
	Fraction operator + (const Fraction &y){
		int resup = up*y.down + y.up*down;
		int resdown = down * y.down;
		int gcd = GCD(resup, resdown);
		return (Fraction){resup/gcd, resdown/gcd};
	}
	Fraction operator * (const Fraction &y){
		int resup = up*y.up;
		int resdown = down*y.down;
		int gcd = GCD(resup, resdown);
		return (Fraction){resup/gcd, resdown/gcd};
	}
	Fraction operator / (const int y){
		int resup = up;
		int resdown = down*y;
		int gcd = GCD(resup, resdown);
		return (Fraction){resup/gcd, resdown/gcd};
	}
	
	inline void Init(int num = 0){
		down = 1;
		up = num;
		return;
	}
	
	inline void Print(){
		printf("%lld %lld\n", up, down);
		return;
	}
}val[MaxN];

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

inline Fraction FRead(){
	int up = Read(), down = Read();
	return (Fraction){up, down};
}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	ind[v]++;
	outd[u]++;
	return;
}

inline void Topo(){
	queue<int> q;
	for(int i=1; i<=m; i++)
		q.push(i);
	while(q.size()){
		int x = q.front();
		q.pop();
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int y = edge[i].destination;
			val[y] = val[y] + val[x] / outd[x];
			ind[y]--;
			if(!ind[y]) q.push(y);
		}
	}
	return;
}

signed main(){
	freopen("water.in", "r", stdin);
	freopen("water.out", "w", stdout);
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		val[i].Init();
		int d = Read();
		for(int j=1; j<=d; j++){
			int a = Read();
			AddEdge(i,a);
		}
	}
	for(int i=1; i<=m; i++)
		val[i].Init(1);
	for(int i=1; i<=n; i++)
		if(!outd[i]) stack[++top] = i;
	Topo();
	for(int i=1; i<=top; i++)
		val[stack[i]].Print();
}
