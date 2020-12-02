#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, father[MaxN];
struct Planet{
	int x, y, z, serial;
}planet[MaxN];
struct Edge{
	int u, v, w;
	bool operator < (const Edge &e)const {
		return w > e.w;
	}
};
priority_queue<Edge> q;

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

inline bool cmpx(Planet a, Planet b){
	return a.x < b.x;
}
inline bool cmpy(Planet a, Planet b){
	return a.y < b.y;
}
inline bool cmpz(Planet a, Planet b){
	return a.z < b.z;
}

inline int Find(int a){
	return father[a] == a ? a : father[a] = Find(father[a]);
}

inline void Merge(int a, int b){
	a = Find(a), b = Find(b);
	if(a != b) father[b] = a;
	return;
}

inline void Init(){
	sort(planet+1, planet+1+n, cmpx);
	for(int i=2; i<=n; i++){
		Edge cur = {planet[i-1].serial, planet[i].serial, abs(planet[i-1].x - planet[i].x)};
		q.push(cur);
	}
	sort(planet+1, planet+1+n, cmpy);
	for(int i=2; i<=n; i++){
		Edge cur = {planet[i-1].serial, planet[i].serial, abs(planet[i-1].y - planet[i].y)};
		q.push(cur);
	}
	sort(planet+1, planet+1+n, cmpz);
	for(int i=2; i<=n; i++){
		Edge cur = {planet[i-1].serial, planet[i].serial, abs(planet[i-1].z - planet[i].z)};
		q.push(cur);
	}
}

inline int Kruskal(){
	int res = 0, tot = 0;
	for(int i=1; i<=n; i++)
		father[i] = i;
	while(true){
		Edge cur = q.top();
		q.pop();
//		printf("%lld\n", cur.w);
		int u = cur.u, v = cur.v;
		if(Find(u) != Find(v)){
			res += cur.w;
			tot++;
			Merge(u,v);
		}
		if(tot == n-1) break;
	}
	return res;
}

signed main(){
//	freopen("stars.in", "r", stdin);
//	freopen("stars.out", "w", stdout);
	n = Read();
	for(int i=1; i<=n; i++){
		int x = Read(), y = Read(), z = Read();
		planet[i] = {x,y,z,i};
	}
	Init();
	int ans = Kruskal();
	printf("%lld", ans);
	return 0;
}