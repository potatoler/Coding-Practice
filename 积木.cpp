#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n,maxn=0;
bool vis[1001];
struct Brick{
	int mx,h[4],x[4],y[4];
}brick[100];

inline void DFS(int H, int x, int y){
	maxn=max(maxn,H);
	for(int i=n;i>=1;i--)
		if(!vis[i]){
			vis[i]=1;
			for(int j=1;j<=3;j++)
				if(brick[i].x[j] <= x && brick[i].y[j] <= y) DFS(H + brick[i].h[j], brick[i].x[j], brick[i].y[j]);
			vis[i]=0;
		}
}

inline void AddBrick(int i, int x, int y, int z){
	brick[i].mx = max(x,max(y,z));
	brick[i].x[1] = min(x,y);
	brick[i].y[1] = max(x,y);
	brick[i].h[1] = z;
	brick[i].x[2] = min(y,z);
	brick[i].y[2] = max(y,z);
	brick[i].h[2] = x;
	brick[i].x[3] = min(x,z);
	brick[i].y[3] = max(x,z);
	brick[i].h[3] = y;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x, y, z;
		scanf("%d%d%d",&x,&y,&z);
		AddBrick(i, x, y, z);
	}
	if(n == 1){
		printf("%d",brick[1].mx);
		return 0;
	}
	for(int i=1;i<=n;i++){
		vis[i]=1;
		for(int j=1;j<=3;j++)
			DFS(brick[i].h[j], brick[i].x[j], brick[i].y[j]);
		vis[i]=0;
	}
	printf("%d",maxn);
	return 0;
}