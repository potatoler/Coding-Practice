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
const double eps = 0.0000001;
struct Vertex{
	double x,y;
}A, B, C, D;
int P, Q, R;

inline double Gougu(Vertex a, Vertex b){
	return sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
}

inline Vertex Find(Vertex a, Vertex b, double k){
	Vertex res;
	res.x = (b.x-a.x) * k + a.x;
	res.y = (b.y-a.y) * k + a.y;
	return res;
}

inline double Calculate(double x, double y){
	Vertex v1 = Find(A,B,x), v2 = Find(C,D,y);
	return Gougu(A,v1) / P + Gougu(v1,v2) / R + Gougu(v2,D) / Q;
}

inline double Check(double x){
	double l=0.0, r=1.0;
	while(r-l >= eps){
		double mid1 = l+(r-l) / 3.0, mid2 = r-(r-l) / 3.0;
		if(Calculate(x,mid1) > Calculate(x,mid2)) l = mid1;
		else r = mid2;
	}
	return Calculate(x,l);
}

signed main(){
	scanf("%lf%lf", &A.x, &A.y), scanf("%lf%lf", &B.x, &B.y);
	scanf("%lf%lf", &C.x, &C.y), scanf("%lf%lf", &D.x, &D.y);
	scanf("%lld%lld%lld", &P, &Q, &R);
	double l=0.0, r=1.0;
	while(r-l >=eps){
		double mid1 = l+(r-l) / 3.0, mid2 = r-(r-l) / 3.0;
		if(Check(mid1) > Check(mid2)) l = mid1;
		else r = mid2;
	}
	printf("%.2lf",Check(l));
	return 0;
}