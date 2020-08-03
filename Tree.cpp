#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 40005;
int n, k, cntEdge, head[MaxN], sumSize, root, number[MaxN], queue[MaxN], top, ans;
struct Vertex{
	int subtreeSize, maxSize, distance, colour, father;
	bool visited;
}vertex[MaxN];
struct Edge{
	int destination, nextEdge, value;
}edge[MaxN*2];
#define thisSon edge[i].destination

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

inline bool cmp(int x, int y){
	return vertex[x].distance < vertex[y].distance;
}

inline void AddEdge(int u, int v, int w){
	cntEdge++;
	edge[cntEdge].destination = v;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].value = w;
	head[u] = cntEdge;
}

inline void GetRoot(int x, int father){
	vertex[x].subtreeSize = 1, vertex[x].maxSize = 0;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father || vertex[thisSon].visited) continue;
//		vertex[thisSon].father = x;
		GetRoot(thisSon, x);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		vertex[x].maxSize = max(vertex[x].maxSize, vertex[thisSon].subtreeSize);
	}
	vertex[x].maxSize = max(vertex[x].maxSize, (sumSize - vertex[x].subtreeSize));
	if(vertex[x].maxSize < vertex[root].maxSize) root = x;
}

inline void GetDistance(int x, int father){
	queue[++top] = x;
	vertex[x].colour = vertex[father].colour;
	number[vertex[x].colour]++;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(thisSon == father || vertex[thisSon].visited) continue;
		vertex[thisSon].distance = vertex[x].distance + edge[i].value;
		GetDistance(thisSon, x);
	}
//	for(int i=1;i<=n;i++)
//		printf("%lld ", vertex[i].distance);
//	printf("\n");
}

inline int Calculate(int x){
	vertex[x].distance = 0, top = 0;
	queue[++top] = x;
	vertex[x].colour = x;
	number[vertex[x].colour] = 1;
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(vertex[thisSon].visited) continue;
		vertex[thisSon].colour = thisSon;
		vertex[thisSon].distance = edge[i].value;
		number[vertex[thisSon].colour] = 0;
		GetDistance(thisSon, thisSon);
	}
	sort(queue+1, queue+1+top, cmp);
	int i = 1, j = top, res = 0;
	while(i < j){
		while(i < j && vertex[queue[i]].distance + vertex[queue[j]].distance <= k){
			res += j - i + 1 - number[vertex[queue[i]].colour];
			number[vertex[queue[i]].colour]--;
			i++;
		}
		number[vertex[queue[j]].colour]--;
		j--;
	}
//	cout<<res<<endl;
//	for(int i=1;i<=n;i++)
//		printf("%lld ", vertex[i].colour);
//	printf("\n");
	return res;
}

inline void Solve(int x){
	vertex[x].visited = true;
	ans += Calculate(x);
	for(int i = head[x]; i; i = edge[i].nextEdge){
		if(vertex[thisSon].visited) continue;
		sumSize = vertex[thisSon].subtreeSize > vertex[x].subtreeSize? n - vertex[x].subtreeSize : vertex[thisSon].subtreeSize;
		root = 0, vertex[root].maxSize = n;
		GetRoot(thisSon, x);
		//cout<<root<<endl;
		Solve(root);
	}
}

signed main(){
	n = Read();
	for(int i=1;i<n;i++){
		int u = Read(), v = Read(), w = Read();
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	k = Read();
	vertex[0].maxSize = sumSize = n;
	GetRoot(1, 0);
	//cout<<root<<endl;
	Solve(root);
	printf("%lld", ans);
	return 0;
}