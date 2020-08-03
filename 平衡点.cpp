#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int MaxN = 1005;
const double deltat = 0.9988;
int n;
double ansx, ansy, answ;
struct{
	int x, y, w;
}object[MaxN];

inline double Energy(double x, double y){
	double energy = 0, deltax, deltay;
	for(int i=1;i<=n;i++){
		deltax = x - object[i].x;
		deltay = y - object[i].y;
		energy += sqrt(deltax*deltax + deltay*deltay) * object[i].w;
	}
	return energy;
}

inline void SimulateAnneal(){
	double t = 3000;
	while(t > 1e-15){
		double newx = ansx + (rand()*2 - RAND_MAX) * t;
		double newy = ansy + (rand()*2 - RAND_MAX) * t;
		double neww = Energy(newx, newy);
		double deltaw = neww - answ;
		if(deltaw < 0){
			ansx = newx;
			ansy = newy;
			answ = neww;
		}
		else if(exp(-deltaw/t) * RAND_MAX > rand()){
			ansx = newx;
			ansy = newy;
		}
		t *= deltat;
	}
}

inline void Solve(){
	SimulateAnneal();
	SimulateAnneal();
	SimulateAnneal();
	SimulateAnneal();
	SimulateAnneal();
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&object[i].x, &object[i].y, &object[i].w);
		ansx += object[i].x;
		ansy += object[i].y;
	}
	ansx /= n;
	ansy /= n;
	answ = Energy(ansx, ansy);
	Solve();
	printf("%.3lf %.3lf", ansx, ansy);
	return 0;
}