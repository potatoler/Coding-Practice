#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 1005;
int lineMax[MaxN][MaxN], lineMin[MaxN][MaxN], columnMax[MaxN][MaxN], columnMin[MaxN][MaxN], square[MaxN][MaxN];
int minQueue[MaxN], maxQueue[MaxN];
int a, b, n, ans = INT_MAX;
int main(){
	scanf("%d%d%d",&a,&b,&n);
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			scanf("%d",&square[i][j]);
	for(int i=1;i<=a;i++){
		int maxHead = 0, minHead = 0, maxTail = 0, minTail = 0;
		for(int j=1;j<=b;j++){
			while(maxHead < maxTail && square[i][j] > square[i][maxQueue[maxTail-1]]) maxTail--;
			while(minHead < minTail && square[i][j] < square[i][minQueue[minTail-1]]) minTail--;
			maxQueue[maxTail++] = j;
			minQueue[minTail++] = j;
			while(maxHead < maxTail && maxQueue[maxTail-1] - maxQueue[maxHead] + 1 > n) maxHead++;
			while(minHead < minTail && minQueue[minTail-1] - minQueue[minHead] + 1 > n) minHead++;
			lineMax[i][j] = square[i][maxQueue[maxHead]];
			lineMin[i][j] = square[i][minQueue[minHead]];
		}
	}
	for(int j=n;j<=b;j++){
		int maxHead = 0, minHead = 0, maxTail = 0, minTail = 0;
		for(int i=1;i<=a;i++){
			while(maxHead < maxTail && lineMax[i][j] > lineMax[maxQueue[maxTail-1]][j]) maxTail--;
			while(minHead < minTail && lineMin[i][j] < lineMin[minQueue[minTail-1]][j]) minTail--;
			maxQueue[maxTail++] = i;
			minQueue[minTail++] = i;
			while(maxHead < maxTail && maxQueue[maxTail-1] - maxQueue[maxHead] + 1 > n) maxHead++;
			while(minHead < minTail && minQueue[minTail-1] - minQueue[minHead] + 1 > n) minHead++;
			columnMax[i][j] = lineMax[maxQueue[maxHead]][j];
			columnMin[i][j] = lineMin[minQueue[minHead]][j];
			if(i < n) continue;
			ans = min(ans, columnMax[i][j] - columnMin[i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}