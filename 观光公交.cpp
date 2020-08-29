#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
const int MaxN = 1003, MaxM = 10004;
int n, m, k, d[MaxN];
struct Passenger{
	int start, end;
}passenger[MaxM];
struct Station{
	int arrive, leave, off;
}station[MaxN];

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

signed main(){
	n = Read(), m = Read(), k = Read();
	for(int i=1; i<n; i++)
		d[i] = Read();
	for(int i=1; i<=m; i++){
		passenger[i].start = Read(); int t = Read(); passenger[i].end = Read();
		station[t].leave = max(station[t].leave, passenger[i].start);
		station[passenger[i].end].off++;
	}
	int maxTime = 0;
	for(int i=1; i<=n; i++){
		station[i].arrive = maxTime;
		maxTime = max(maxTime, station[i].leave);
		maxTime += d[i];
	}
	int maxNum, maxPos, tmpNum;
	while(k--){
		maxNum = 0;
		for(int i=2; i<=n; i++){
			if(!d[i-1]) continue;
			tmpNum = 0;
			for(int j=i; j<=n; j++){
				tmpNum += station[j].off;
				if(station[j].arrive <= station[j].leave) break;
			}
			if(tmpNum > maxNum){
				maxNum = tmpNum;
				maxPos = i;
			}
		}
		d[maxPos-1]--;
		for(int i=maxPos; i<=n; i++){
			station[i].arrive--;
			if(station[i].arrive < station[i].leave) break;
		}
	}
	int ans = 0;
	for(int i=1; i<=m; i++)
		ans += station[passenger[i].end].arrive - passenger[i].start;
	printf("%lld", ans);
	return 0;
}