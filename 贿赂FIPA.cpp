#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<map>
#define int long long
using namespace std;
const int MaxN = 202;
int n, m, a[MaxN], father[MaxN], subtreeSize[MaxN];
int head[MaxN], cntEdge, f[MaxN][MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
string s,t;
map<string, int> st;

inline int Read(){
	char c = getchar();
    if (c == '#') return -1;
    while (c < '0' || c > '9') c = getchar();
    int ans = 0;
    while (c >= '0' && c <= '9')
    {
        ans = (ans << 3) + (ans << 1) + (c ^ '0');
        c = getchar();
    }
    return ans;
}

inline void AddEdge(int u, int v){
	cntEdge++;
	father[v] = u;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	head[u] = cntEdge;
	return;
}

inline void DFS(int u){
	f[u][0] = 0, subtreeSize[u] = 1;
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		DFS(v);
		subtreeSize[u] += subtreeSize[v];
	}
	// cout<<"sizeof"<<u<<":"<<subtreeSize[u]<<endl;
	for(int i = head[u]; i; i = edge[i].nextEdge){
		int v = edge[i].destination;
		for(int j=subtreeSize[u]; j>=0; j--){
			for(int k=min(subtreeSize[v],j); k>=1; k--){
				f[u][j] = min(f[u][j], f[u][j-k]+f[v][k]);
				// cout<<f[u][j]<<endl;
			}
		}
	}
	if(u) for(int j=0; j<=subtreeSize[u]; j++) f[u][j] = min(f[u][j], a[u]);
}

signed main(){
	while(n = Read(), n!=-1){
		m = Read();
		map<string, int>().swap(st);
		memset(f, 0x3f, sizeof(f));
		for(int i=0; i<=n; i++){
			father[i] = i;
			f[i][0] = head[i] = 0;
		}
		st[""] = 0;
		cntEdge = 0;
		for(int i=1; i<=n; i++){
			cin >> s;
			int idxs;
			if(st.count(s)) idxs = st[s];
			else idxs = st.size(), st[s] = idxs;
			cin>>a[idxs];
			char ch;
			while((ch = getchar()) != '\n'){
				cin >> t;
				int idxt;
				if(st.count(t)) idxt = st[t];
				else idxt = st.size(), st[t] = idxt;
				AddEdge(idxs, idxt);
			}
		}
		for(int i=1; i<=n; i++)
			if(father[i] == i) AddEdge(0, i);
		DFS(0);
		printf("%lld\n", f[0][m]);
	}
	return 0;
}