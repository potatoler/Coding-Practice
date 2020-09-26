#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
int n, sx, sy, dx, dy, t, mod;
int tmp[6][6] = {
	{2, 1, 1, 0, 1, 2}, // sx (t-1 -> t)
	{1, 2, 0, 1, 1, 2}, // sy (t-1 -> t)
	{1, 1, 1, 0, 1, 2}, // dx (t-1 -> t)
	{1, 1, 0, 1, 1, 2}, // dy (t-1 -> t)
	{0, 0, 0, 0, 1, 1}, // t-1 -> t
	{0, 0, 0, 0, 0, 1}  // 1 (constant)
};

struct Matrix{
	int num[6][6];
	Matrix(){memset(num, 0, sizeof(num));}
	inline void Init(){
		for(int i=0; i<6; i++)
			num[i][i] = 1;
	}
}parameters, ans;

inline Matrix operator * (Matrix a, Matrix b){
	Matrix res;
	for (int i=0;i<6;i++)
		for (int j=0;j<6;j++)
			for (int k=0;k<6;k++)
				res.num[i][j] = (res.num[i][j] + a.num[i][k] * b.num[k][j] % n + n) % n;
	return res;
}

signed main(){
	scanf("%lld%lld%lld%lld%lld%lld", &n, &sx, &sy, &dx, &dy, &t);
	int arguments[6] = {sx-1, sy-1, dx, dy, 0, 1};
	memcpy(parameters.num, tmp, sizeof(tmp));
	ans.Init();
	
	if(!t){
		printf("%lld %lld", sx, sy);
		return 0;
	}

	while(t){
		if(t&1) ans = ans * parameters;
		parameters = parameters * parameters;
		t >>= 1;
	}
			
	int cx=0,cy=0;
	for(int i=0; i<6; i++){
		cx = (cx + arguments[i] * ans.num[0][i] % n + n) % n;
		cy = (cy + arguments[i] * ans.num[1][i] % n + n) % n;
	}
	printf("%lld %lld", cx+1, cy+1);
	
	return 0;
}