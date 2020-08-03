#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int T, d, a[11], cnt, f[1<<11][1005];
char s[1<<11];
bool visited[1<<11];

signed main(){
	scanf("%lld", &T);
	while(T--){
		memset(f, 0, sizeof(f));
		cnt = 0;
		scanf("%s%lld", s+1, &d);
		int len = strlen(s+1);
		for(int i=1; i<=len; i++)
			a[i] = s[i] - '0';
		f[0][0] = 1;
		for(int s=0; s < (1<<len)-1; s++){
			memset(visited, false, sizeof(visited));
			for(int j=1; j<=len; j++) if(!(s & (1<<(j-1))) && !visited[a[j]]){
				visited[a[j]] = true;
				for(int k=0; k<d; k++)
					f[s | (1<<(j-1))][(k * 10 + a[j]) % d] += f[s][k];
			}
		}
		printf("%lld\n",f[(1<<len)-1][0]);
	}
	return 0;
}