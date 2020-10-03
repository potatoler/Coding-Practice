#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 5003;
int cntA[MaxN], cntT[MaxN], cntG[MaxN], cntC[MaxN], n, ans;
char ch[MaxN];

signed main(){
	scanf("%lld %s", &n, ch+1);
	for(int i=1; i<=n; i++){
		if(ch[i] == 'A') cntA[i]++;
		if(ch[i] == 'T') cntT[i]++;
		if(ch[i] == 'G') cntG[i]++;
		if(ch[i] == 'C') cntC[i]++;
		cntA[i] += cntA[i-1];
		cntT[i] += cntT[i-1];
		cntG[i] += cntG[i-1];
		cntC[i] += cntC[i-1];
	}
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j++)
			if(cntA[j] - cntA[i-1] == cntT[j] - cntT[i-1] && cntG[j] - cntG[i-1] == cntC[j] - cntC[i-1]) ans++;
	printf("%lld", ans);
	return 0;
}