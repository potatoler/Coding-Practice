#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<queue>
using namespace std;
const int MaxN = 35;
const int inf=99999999;
int n, m, q, ex, ey, bx, by, cx, cy;
bool mapp[MaxN][MaxN];
int xx[4]={-1,1,0,0};
int yy[4]={0,0,-1,1};
int getnum(int ax,int ay,int t){
	return ((ax-1)*m+ay)*4-(4-t);
} 
struct white{
	int x,y;
	int step;
};
bool judge(int ax,int ay){
	if(ax<=0||ax>n||ay<=0||ay>m)return 0;
	return mapp[ax][ay];
}
bool vis[MaxN][MaxN];
int bfs(int dx,int dy,int sx,int sy,int tx,int ty){
	queue<white>q;
	memset(vis,0,sizeof vis);
	white st;st.x=sx;st.y=sy;
	st.step=0;vis[sx][sy]=1;
	q.push(st);
	while(!q.empty()){
		white noww=q.front();
		q.pop();
		if(noww.x==tx&&noww.y==ty)
		return noww.step;
		for(int i=0;i<4;i++){
			if(judge(noww.x+xx[i],noww.y+yy[i])){
				if(vis[noww.x+xx[i]][noww.y+yy[i]])continue;
				if(noww.x+xx[i]==dx&&noww.y+yy[i]==dy)continue; 
				white nxt;
				nxt.x=noww.x+xx[i];
				nxt.y=noww.y+yy[i];
				nxt.step=noww.step+1;
				q.push(nxt);vis[noww.x+xx[i]][noww.y+yy[i]]=1;
			}
		}
	}
	return inf;
}
struct edge{
	int to,nxt,dis;
}b[5005];
int head[5005],tot;
void add(int u,int v,int w){
	b[++tot].to=v;b[tot].nxt=head[u];
	b[tot].dis=w;head[u]=tot;
}
bool ok[MaxN][MaxN][5];
void init(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(!mapp[i][j])continue;
		for(int k=0;k<4;k++)
		if(judge(i+xx[k],j+yy[k]))ok[i][j][k]=1;
		}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
    for(int k=0;k<4;k++)
	for(int l=k+1;l<4;l++){
		if(ok[i][j][k]&&ok[i][j][l]){
			int aa=getnum(i,j,k);
			int bb=getnum(i,j,l);
			int cc=bfs(i,j,i+xx[k],j+yy[k],i+xx[l],j+yy[l]);
			if(cc==inf)continue;
			add(aa,bb,cc);add(bb,aa,cc);
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<m;j++){
		if(ok[i][j][3]&&ok[i][j+1][2]){ 
			int aa=getnum(i,j,3);
			int bb=getnum(i,j+1,2);
			add(aa,bb,1);add(bb,aa,1);
		}
	}
	for(int i=1;i<n;i++)
	for(int j=1;j<=m;j++){
		if(ok[i][j][1]&&ok[i+1][j][0]){
			int aa=getnum(i,j,1);
			int bb=getnum(i+1,j,0);
			add(aa,bb,1);add(bb,aa,1);
		}
	}
}
queue<int>Q;
bool viss[5005];
int d[5005];
void work(){
	memset(d,128/3,sizeof d);
	memset(viss,0,sizeof viss);
	for(int i=0;i<4;i++){
		if(judge(bx+xx[i],by+yy[i])){
			int nw=bfs(bx,by,ex,ey,bx+xx[i],by+yy[i]);
			if(nw==inf)continue; 
			int nq=getnum(bx,by,i);
			d[nq]=nw;
			Q.push(nq);
			viss[nq]=1;
		}
	}
	while(!Q.empty()){
		int noww=Q.front();Q.pop();viss[noww]=0;
		for(int j=head[noww];j;j=b[j].nxt){
			int vv=b[j].to;
			if(d[vv]>d[noww]+b[j].dis){
				d[vv]=d[noww]+b[j].dis;
				if(!viss[vv])Q.push(vv),viss[vv]=1;
			}
		}
	}
	int ans=inf;
	for(int i=0;i<4;i++){
		int qaq=getnum(cx,cy,i);
		ans=min(ans,d[qaq]);
	}
	if(ans==inf)puts("-1");
	else printf("%d\n",ans);
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)cin>>mapp[i][j];
	init();
	while(q--){
		scanf("%d%d%d%d%d%d",&ex,&ey,&bx,&by,&cx,&cy);
		if(bx==cx&&by==cy){
			puts("0");
			continue;
		}
		if(!mapp[cx][cy]){
			puts("-1");
			continue;
		}
		if(!mapp[bx][by]){
			puts("-1");
			continue;
		}
		work();
	}
	return 0;
}
