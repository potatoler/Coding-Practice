#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n, m, fx, fy, sx, sy, maze[105][105];
double cntCr, cntLe, s, ans;
struct Point{int x, y;};
Point lastPoint[105][105];
bool vis[105][105];
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

bool Check(int x, int y){
	if (!vis[x][y] && maze[x][y] == 0 && x <= n 
		&& y <= m && x >= 1 && y >= 1) return true;
	return false;
}

void BFS(){
	Point thisPoint, nextPoint;
	thisPoint.x = fx;
	thisPoint.y = fy;
	queue<Point> q;
	q.push(thisPoint);
	while (!q.empty()){
		thisPoint = q.front();
		q.pop();
		if(thisPoint.x == sx && thisPoint.y == sy) break;
		int tmp_x, tmp_y;
		for (int i = 0; i < 4; i++){
			tmp_x = thisPoint.x + dx[i];
			tmp_y = thisPoint.y + dy[i];
			if(Check(tmp_x, tmp_y)){
				nextPoint.x = tmp_x;
				nextPoint.y = tmp_y;
				lastPoint[nextPoint.x][nextPoint.y].x = thisPoint.x;
				lastPoint[nextPoint.x][nextPoint.y].y = thisPoint.y;
				vis[nextPoint.x][nextPoint.y] = 1;
				q.push(nextPoint);
			}
		}
	}

}

void Statistic(){
	int x = sx, y = sy;
	while (!(x == fx && y == fy)){
		int tmp_x, tmp_y;
		tmp_x = lastPoint[x][y].x;
		tmp_y = lastPoint[x][y].y;
		if(x == tmp_x) cntCr += 1.0;
		else if(y == tmp_y) cntLe += 1.0;
		x = tmp_x;
		y = tmp_y;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d",&sx,&sy,&fx,&fy);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&maze[i][j]);
	scanf("%lf",&s);
	BFS();
	Statistic();
	//printf("%.0lf %.0lf\n",cntCr, cntLe);
	ans = (s - cntCr) / cntLe;
	printf("%.3lf",ans);
	return 0;
}