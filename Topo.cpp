#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
using namespace std;
const int MaxN = 102, MaxM= 202;
vector<int> to[MaxN], res;
int n, m, st, ed, degree[MaxN], edge[MaxN][MaxN], f[MaxN][MaxN];
int lv, ar;
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

inline void Topo(){
	queue<int> q;
	for(int i=1; i<=n; i++)
		if(!degree[i]) q.push(i);
	while(q.size()){
		int x = q.front();
		q.pop();
		res.push_back(x);
		if(x == st)
			lv = res.end() - res.begin() - 1;
		if(x == ed)
			ar = res.end() - res.begin() - 1;
		for(int i=0; i<to[x].size(); i++){
			int y = to[x][i];
			degree[y]--;
			if(!degree[y]) q.push(y);
		}
	}
}

signed main(){
	n = Read(), m = Read(), st = Read(), ed = Read();
	for(int i=1; i<=m; i++){
		int u = Read(), v = Read();
		edge[u][v]++;
		to[u].push_back(v);
		degree[v]++;
	}
	Topo();
	for(int i=1; i<=n; i++)
		f[i][i] = 1;
//	for(int i=0; i<res.size();i++)
//		printf("%d ", res[i]);
	for(int i=lv+1; i<=ar; i++){
		for(int j=lv; j<i; j++){
			if(edge[res[j]][res[i]])
				f[st][res[i]] += f[st][res[j]] * edge[res[j]][res[i]];
		}
	}
	printf("%d", f[st][ed]);
	return 0;
}