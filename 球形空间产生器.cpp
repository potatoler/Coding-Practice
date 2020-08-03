//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
//#pragma GCC optimize("-fgcse-lm")
//#pragma GCC optimize("-fipa-sra")
//#pragma GCC optimize("-ftree-pre")
//#pragma GCC optimize("-ftree-vrp")
//#pragma GCC optimize("-fpeephole2")
//#pragma GCC optimize("-ffast-math")
//#pragma GCC optimize("-fsched-spec")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("-falign-jumps")
//#pragma GCC optimize("-falign-loops")
//#pragma GCC optimize("-falign-labels")
//#pragma GCC optimize("-fdevirtualize")
//#pragma GCC optimize("-fcaller-saves")
//#pragma GCC optimize("-fcrossjumping")
//#pragma GCC optimize("-fthread-jumps")
//#pragma GCC optimize("-funroll-loops")
//#pragma GCC optimize("-fwhole-program")
//#pragma GCC optimize("-freorder-blocks")
//#pragma GCC optimize("-fschedule-insns")
//#pragma GCC optimize("inline-functions")
//#pragma GCC optimize("-ftree-tail-merge")
//#pragma GCC optimize("-fschedule-insns2")
//#pragma GCC optimize("-fstrict-aliasing")
//#pragma GCC optimize("-fstrict-overflow")
//#pragma GCC optimize("-falign-functions")
//#pragma GCC optimize("-fcse-skip-blocks")
//#pragma GCC optimize("-fcse-follow-jumps")
//#pragma GCC optimize("-fsched-interblock")
//#pragma GCC optimize("-fpartial-inlining")
//#pragma GCC optimize("no-stack-protector")
//#pragma GCC optimize("-freorder-functions")
//#pragma GCC optimize("-findirect-inlining")
//#pragma GCC optimize("-fhoist-adjacent-loads")
//#pragma GCC optimize("-frerun-cse-after-loop")
//#pragma GCC optimize("inline-small-functions")
//#pragma GCC optimize("-finline-small-functions")
//#pragma GCC optimize("-ftree-switch-conversion")
//#pragma GCC optimize("-foptimize-sibling-calls")
//#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("-funsafe-loop-optimizations")
//#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const double deltaT = 0.9996;
const int MaxN = 15;
int n;
double kotaenoZahyo[MaxN], tennoZahyo[MaxN][MaxN], zanteZahyo[MaxN], zahyonoHenkou[MaxN];
double atarashiiZahyo[MaxN], kotaenoEnergy, atarashiiEnergy;

inline double Energy(double zahyo[]){
	//double energy = 0;
	double maxEnergy = 0, minEnergy = 1e20;
	for(int i=1;i<=n+1;i++){
		double zanteEnergy = 0;
		for(int j=1;j<=n;j++){
			zahyonoHenkou[j] = zahyo[j] - tennoZahyo[i][j];
			zanteEnergy += zahyonoHenkou[j] * zahyonoHenkou[j];
		}
		maxEnergy = max(maxEnergy, zanteEnergy);
		minEnergy = min(minEnergy, zanteEnergy);
//		energy += sqrt(zanteEnergy);
	}
	return maxEnergy - minEnergy;
//	return energy;
}

inline void SimulateAnneal(){
	double t = 1e15;
	while(t >= 1e-15){
		for(int i=1;i<=n;i++)
			atarashiiZahyo[i] = kotaenoZahyo[i] + (rand()*2 - RAND_MAX) * t;
		double atarashiiEnergy = Energy(atarashiiZahyo);
		double energynoHenko = atarashiiEnergy - kotaenoEnergy;
		if(energynoHenko < 0){
			for(int j=1;j<=n;j++)
				kotaenoZahyo[j] = atarashiiZahyo[j];
			kotaenoEnergy = atarashiiEnergy;
		}
		else if(exp(-energynoHenko/t) * RAND_MAX > rand()){
			for(int j=1;j<=n;j++)
				kotaenoZahyo[j] = atarashiiZahyo[j];
		}
		t *= deltaT;
	}
}

inline void Solve(){
	SimulateAnneal();
//	SimulateAnneal();
//	SimulateAnneal();
//	SimulateAnneal();
//	SimulateAnneal()4;
}

int main(){
	srand(20040525);
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=n;j++){
			scanf("%lf",&tennoZahyo[i][j]);
			kotaenoZahyo[j] += tennoZahyo[i][j];
		}
	}
	for(int i=1;i<=n;i++)
		kotaenoZahyo[i] /= n+1;
	kotaenoEnergy = Energy(kotaenoZahyo);
	//printf("%.3lf\n",kotaenoEnergy);
	Solve();
	for(int i=1;i<=n;i++)
		printf("%.3lf ",kotaenoZahyo[i]);
	return 0;
}