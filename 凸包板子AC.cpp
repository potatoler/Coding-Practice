#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;
const int MaxN = 100005;
int n, top;
struct Vertex{
	double x, y;
}vertex[MaxN], tubao[MaxN];

double ans;

inline bool Cross(Vertex p1, Vertex p2, Vertex p3){
	return (p2.x - p3.x) * (p1.y - p2.y) > (p1.x - p2.x) * (p2.y - p3.y);
}

inline double Distance(Vertex p1, Vertex p2){
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

inline bool cmp(Vertex a, Vertex b){
	return (a.y==b.y)? (a.x<b.x) : (a.y<b.y);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf", &vertex[i].x, &vertex[i].y);
	sort(vertex+1, vertex+1+n, cmp);
	top = 2;
	tubao[1] = vertex[1];
	tubao[2] = vertex[2];
	for(int i=3;i<=n;i++){
		while(top > 1 && !Cross(vertex[i], tubao[top], tubao[top-1])) top--;
		tubao[++top] = vertex[i];
	}
	for(int i=1;i<top;i++)
		ans += Distance(tubao[i], tubao[i+1]);
//	for(int i=1;i<=top;i++)
//		printf("%.2lf %.2lf\n", tubao[i].x, tubao[i].y);
	top = 2;
	tubao[1] = vertex[1];
	tubao[2] = vertex[2];
	for(int i=3;i<=n;i++){
		while(top > 1 && Cross(vertex[i], tubao[top], tubao[top-1])) top--;
		tubao[++top] = vertex[i];
	}
	for(int i=1;i<top;i++)
		ans += Distance(tubao[i], tubao[i+1]);
//	for(int i=1;i<=top;i++)
//		printf("%.2lf %.2lf\n", tubao[i].x, tubao[i].y);
	printf("%.2lf", ans);
	return 0;
}
