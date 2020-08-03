#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<queue>
#include<stack>
#define int long long
using namespace std;
const int MaxN = 1003;
int n, s, t, cntEdge, head[MaxN], score[MaxN], fr[MaxN];
double dis[MaxN];
struct Flag{
	int o, A, B, k;
}flag[MaxN];
struct Edge{
	int destination, nextEdge;
	double value;
}edge[MaxN * 2];
bool visited[MaxN];
queue<int> q;

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

inline void AddEdge(int u, int v, double w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
	return;
}

inline bool Check(double T){
	memset(head, 0, sizeof(head));
	memset(fr, 0, sizeof(fr));
	while(q.size()) q.pop();
	cntEdge = 0;
	for(int i=0;i<=n;i++)
		dis[i] = 1, fr[i] = 0, visited[i] = true, q.push(i);
	for(int i=1;i<=n;i++)
		if(score[i]) AddEdge(i, 0, 1.0/score[i]), AddEdge(0, i, score[i]);
	for(int i=1;i<=s;i++){
		int A = flag[i].A, B = flag[i].B, k = flag[i].k, o = flag[i].o;
		if(o == 1) AddEdge(B, A, k-T);
		else AddEdge(B, A, 1.0/(k+T));
	}
	while(q.size()){
		int x = q.front();
		for(int i = head[x]; i; i = edge[i].nextEdge){
			int des = edge[i].destination;
			if(dis[des] >= dis[x] * edge[i].value) continue;
			dis[des] = dis[x] * edge[i].value;
			fr[des] = fr[x] + 1;
			if(fr[des] == n+2) return true;
			if(!visited[des]) q.push(des),visited[des] = true;
		}
		q.pop();
		visited[x] = false;
	}
//	for(int i=1;i<=n;i++)
//		printf("%.10lf\n", dis[i]);
	return false;
}

signed main(){
	n = Read(), s = Read(), t = Read();
	double l=0, r=1e18, T = -1;
	for(int i=1;i<=s;i++){
		int o = Read(), A = Read(), B = Read(), k = Read();
		flag[i] = (Flag){o, A, B, k};
		if(o == 1) r = min(r, (double)k-1e-8);
	}
	for(int i=1;i<=t;i++){
		int C = Read(), x = Read();
		score[C] = x;
	}
	while(r - l > 1e-8){
		double mid = (l + r) / 2;
		Check(mid)? l = T = mid : r = mid;
	}
	if(T == -1) printf("-1\n");
	else printf("%.10lf\n",T);
	return 0;
}