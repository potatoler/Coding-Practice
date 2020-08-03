#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MaxN = 50005, Mod = 201314;
int n, m, cntEdge, cntDFN, pos[MaxN], head[MaxN], Ans[MaxN];
struct Edge{
	int destination, nextEdge;
}edge[MaxN*2];
struct Vertex{
	int father, chainTop, DFN, heavySon, depth, subtreeSize;
}vertex[MaxN];
struct SegmentTree{
	int l, r, sum, lazyTag;
}seg[MaxN*4];
struct Question{
	int x, y, pos;
}question[MaxN*4];
#define thisSon edge[i].destination
#define xTop vertex[x].chainTop
#define yTop vertex[y].chainTop

inline bool cmpQuestion(Question a, Question b){
	return a.x < b.x;
}

inline void AddEdge(int u, int v){
	cntEdge++;
	edge[cntEdge].nextEdge = head[u];
	edge[cntEdge].destination = v;
	head[u] = cntEdge;
}

inline void DFS1(int x){
	vertex[x].subtreeSize = 1;
	for(int i=head[x]; i; i=edge[i].nextEdge){
		vertex[thisSon].father = x;
		vertex[thisSon].depth = vertex[x].depth + 1;
		DFS1(thisSon);
		vertex[x].subtreeSize += vertex[thisSon].subtreeSize;
		if(vertex[thisSon].subtreeSize > vertex[vertex[x].heavySon].subtreeSize) vertex[x].heavySon = thisSon;
	}
}

inline void DFS2(int x, int top){
	vertex[x].DFN = ++cntDFN;
	pos[vertex[x].DFN] = x;
	vertex[x].chainTop = top;
	if(!vertex[x].heavySon) return;
	DFS2(vertex[x].heavySon, top);
	for(int i=head[x]; i; i=edge[i].nextEdge){
		if(thisSon == vertex[x].father || thisSon == vertex[x].heavySon) continue;
		DFS2(thisSon, thisSon);
	}
}

inline void Build(int x, int l, int r){
	seg[x].l = l;
	seg[x].r = r;
	if(seg[x].l == seg[x].r) return;
	int mid = (l + r) / 2;
	Build(x*2, l, mid);
	Build(x*2+1, mid+1, r);
}

inline void PassTag(int x){
	int mid = (seg[x].l = seg[x].r) / 2;
	seg[x*2].sum += 1LL* (mid-seg[x].l+1) * seg[x].lazyTag % Mod;
	seg[x*2+1].sum += 1LL* (seg[x].r-mid) * seg[x].lazyTag % Mod;
	seg[x*2].lazyTag += seg[x].lazyTag;
	seg[x*2+1].lazyTag += seg[x].lazyTag;
	seg[x].lazyTag = 0;
}

inline void Update(int x, int l, int r){
	if(l <= seg[x].l && seg[x].r >= r){
		seg[x].sum += seg[x].r - seg[x].l + 1;
		seg[x].lazyTag++;
		return;
	}
	PassTag(x);
	int mid = (seg[x].l + seg[x].r) / 2;
	if(l <= mid) Update(x*2, l, r);
	if(r > mid) Update(x*2+1, l, r);
	seg[x].sum = seg[x*2].sum + seg[x*2+1].sum;
}

int Ask(int x, int l, int r){
	if(l <= seg[x].l && seg[x].r >= r) return seg[x].sum;
	PassTag(x);
	int mid = (seg[x].l + seg[x].r) / 2, ans = 0;
	if(l <= mid) ans += Ask(x*2, l, r);
	if(r > mid) ans += Ask(x*2+1, l, r);
	seg[x].sum = seg[x*2].sum + seg[x*2+1].sum;
	return ans;
}

inline void ChainUpdate(int x){
	while(x){
		Update(1, vertex[xTop].DFN, vertex[x].DFN);
		x = vertex[xTop].father;
	}
}

inline int ChainAsk(int x){
	int ans = 0;
	while(x){
		ans += Ask(1, vertex[xTop].DFN, vertex[x].DFN);
		x = vertex[x].father;
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		scanf("%d",&vertex[i].father);
		AddEdge(
		++vertex[i].father, i);
	}
	Build(1,1,n);
	DFS1(1);
	DFS2(1,1);
	for(int i=1;i<=m;i++){
		int l, r, z;
		scanf("%d%d%d",&l,&r,&z);
		l++; r++; z++;
		question[i*2-1] = (Question){r, z, i*2-1};
		question[i*2] = (Question){l-1, z, i*2};
	}
	sort(question+1, question+1+m*2, cmpQuestion);
	int cur = 1;
	while(question[cur].x == 0 && cur <= m*2){
		int tmp = ChainAsk(question[cur].y);
		if(question[cur].pos & 1) Ans[(question[cur].pos+1)/2] += tmp;
		else Ans[(question[cur].pos+1)/2] -= tmp;
		cur++;
	}
	for(int i=1;i<=n;i++){
		ChainUpdate(i);
		while(question[cur].x == 0 && cur <= m*2){
			int tmp = ChainAsk(question[cur].y);
			if(question[cur].pos & 1) Ans[(question[cur].pos+1)/2] += tmp;
			else Ans[(question[cur].pos+1)/2] -= tmp;
			cur++;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",(Ans[i]%Mod + Mod) % Mod);
		return 0;
}