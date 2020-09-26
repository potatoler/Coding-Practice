#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int x, n, m, digits, cnt;
double p, ans, f[203][303][303][2];

inline int CountZero(int x){
	int cnt = 0;
	while(x % 2 == 0){
		cnt++;
		x /= 2;
	}
	return cnt;
}

signed main(){
	scanf("%lld%lld%lf", &x, &n, &p);
	p /= 100;
	int tmp = x, opt = (tmp >>= 8) & 1;
	digits = (1<<8)-1;
	while(tmp && (tmp&1)==opt){
		cnt++;
		tmp >>= 1;
	}
	if(cnt == 0) cnt++;
	m = cnt+n;
	f[0][x&digits][cnt][opt] = 1;
	
	for(int i=1; i<=n; i++){
		for(int trailing = 0; trailing <= digits; trailing++){
			for(int same = 1; same <= m; same++){
				for(int ninth = 0; ninth <= 1; ninth++){
					if(f[i-1][trailing][same][ninth]){
						int newTrailing, newSame, newNinth;
						newTrailing = trailing+1;
						if(newTrailing == (1<<8)){
							newTrailing = 0;
							newNinth = ninth ^ 1;
							if(ninth == 1) newSame = same;
							else newSame = 1;
						}
						else newSame = same, newNinth = ninth;
						f[i][newTrailing][newSame][newNinth] += f[i-1][trailing][same][ninth] * (1-p);
						newTrailing = trailing << 1;
						if(((newTrailing >> 8) & 1) == ninth) newNinth = ninth, newSame = same + 1;
						else newNinth = ninth ^ 1, newSame = 1;
						newTrailing = newTrailing & digits;
						f[i][newTrailing][newSame][newNinth] += f[i-1][trailing][same][ninth] * p;
					}
				}
			}
		}
	}
	
	for(int trailing = 1; trailing <= digits; trailing++){
		for(int same = 1; same <= m; same++){
			for(int ninth = 0; ninth <= 1; ninth++){
				if(f[n][trailing][same][ninth]) ans += f[n][trailing][same][ninth] * CountZero(trailing);
			}
		}
	}
	
	for(int same = 1; same <= m; same++)
		ans += f[n][0][same][0] * (same + 8) + f[n][0][same][1] * 8;
	printf("%.13lf", ans);
	return 0;
}