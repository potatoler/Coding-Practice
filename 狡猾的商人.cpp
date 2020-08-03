#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 105;
int fa[MaxN], DS[MaxN], T, n, m;

int Find(int x){
	if(x != fa[x]){
		int tmp = Find(fa[x]);
		DS[x] += DS[fa[x]];
		fa[x] = tmp;
	}
	return fa[x];
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d", &n, &m);
		bool nise = false;
		for(int i=0;i<=n;i++){
			fa[i] = i;
			DS[i] = 0;
		}
		for(int i=1;i<=m;i++){
			int x, y, z;
			scanf("%d%d%d",&x,&y,&z);
			x--;
			if(Find(x) != Find(y)){
				DS[fa[y]] = DS[x] - DS[y] - z;
				fa[fa[y]] = fa[x];
			}
			else if(DS[x] - DS[y] != z) nise = true;
		}
		if(nise) printf("false\n");
		else printf("true\n");
	}
	return 0;
}