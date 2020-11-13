#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 1003;
int T, n, m, hp, mp, sp, dhp, dmp, dsp, x, ans;
int a[MaxN], b[MaxN], y[MaxN], c[MaxN], z[MaxN], n1, n2;
int fmp[MaxN][MaxN], fsp[MaxN][MaxN], fhp[MaxN][MaxN];
int max_fmp[MaxN], max_fsp[MaxN], max_fhp[MaxN], max_fsum[MaxN];

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

inline void Input(){
	n = Read(), m = Read(), hp = Read(), mp = Read(), sp = Read(), dhp = Read(), dmp = Read(), dsp = Read(), x = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	n1 = Read();
	for(int i=1; i<=n1; i++)
		b[i] = Read(), y[i] = Read();
	n2 = Read();
	for(int i=1; i<=n2; i++)
		c[i] = Read(), z[i] = Read();
	return;
}

inline void Init(){
	memset(fmp, -0x3f3f3f3f, sizeof(fmp));
	memset(fhp, -0x3f3f3f3f, sizeof(fhp));
	memset(fsp, -0x3f3f3f3f, sizeof(fsp));
	memset(max_fmp, -0x3f3f3f3f, sizeof(max_fmp));
	memset(max_fsp, -0x3f3f3f3f, sizeof(max_fsp));
	memset(max_fhp, -0x3f3f3f3f, sizeof(max_fhp));
	memset(max_fsum, -0x3f3f3f3f, sizeof(max_fsum));
	return;
}

inline void MP_DP(){
	fmp[0][mp] = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<=mp; j++){
			fmp[i+1][min(j+dmp,mp)] = max(fmp[i+1][min(j+dmp,mp)], fmp[i][j]);
			for(int k=1; k<=n1; k++)
				if(j >= b[k]) fmp[i+1][j-b[k]] = max(fmp[i+1][j-b[k]], fmp[i][j] + y[k]);
		}
	}
	for(int i=0; i<=n; i++)
		for(int j=0; j<=mp; j++)
			max_fmp[i] = max(max_fmp[i], fmp[i][j]);
	return;
}

inline void SP_DP(){
	fsp[0][sp] = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<=sp; j++){
			fsp[i+1][min(j+dsp,sp)] = max(fsp[i+1][min(j+dsp,sp)], fsp[i][j] + x);
			for(int k=1; k<=n2; k++){
				if(j >= c[k]) fsp[i+1][j-c[k]] = max(fsp[i+1][j-c[k]], fsp[i][j] + z[k]);
			}
		}
	}
	for(int i=0; i<=n; i++)
		for(int j=0; j<=sp; j++)
			max_fsp[i] = max(max_fsp[i], fsp[i][j]);
	return;
}

inline void HP_DP(){
	fhp[1][hp] = 1;
	for(int i=1; i<=n; i++){
		for(int j=a[i]+1; j<=hp; j++){
			fhp[i+1][min(j+dhp-a[i],hp)] = max(fhp[i+1][min(j+dhp-a[i],hp)], fhp[i][j]);
			fhp[i+1][j-a[i]] = max(fhp[i+1][j-a[i]], fhp[i][j] + 1);
		}
	}
	for(int i=1; i<=n+1; i++)
		for(int j=1; j<=hp; j++)
			max_fhp[i] = max(max_fhp[i], fhp[i][j]);
	return;
}

inline void Sum_DP(){
	for(int i=0; i<=n; i++)
		for(int j=0; i+j<=n; j++)
			max_fsum[i+j] = max(max_fsum[i+j], max_fmp[i] + max_fsp[j]);
	return;
}

inline void Statistic(){
	int flag = 0;
	for(int i=1; i<=n && flag == 0; i++){
		if(max_fhp[i] > 0 && max_fsum[max_fhp[i]] >= m){
			flag = 1;
			ans = i;
		}
	}
	int tmp = hp;
	for(int i=1; i<=n && flag == 0; i++){
		tmp = min(tmp+dhp, hp);
		if(tmp - a[i] <= 0) flag = -1;
		tmp -= a[i];
	}
//	printf("\n");
//	printf("%lld\n", tmp);
	if(flag == 1) printf("Yes %lld\n", ans);
	else if(flag == -1) printf("No\n");
	else printf("Tie\n");
	return;
}

signed main(){
	T = Read();
	while(T--){
		Input();
		Init();
		MP_DP();
		SP_DP();
		HP_DP();
		Sum_DP();
		Statistic();
	}
	return 0;
}