#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long 
using namespace std;
const int MaxN = 100005;
char str[MaxN], ans[MaxN];

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

inline bool OverFlow(int len, int mid){
	for(int i=1; i<=mid; i++)
		if(str[i] != '7') return str[i] > '7';
	for(int i=1; i<=mid; i++)
		if(str[i+mid] != '4') return str[i+mid] > '4';
	return 0;
}

signed main(){
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	while(scanf("%s", str+1) == true){
		int len = strlen(str+1);
		int mid = len >> 1;
		if(len & 1 || OverFlow(len, mid)){
			mid++;
			for(int i=1; i<=mid; i++)
				printf("4");
			for(int i=1; i<=mid; i++)
				printf("7");
			printf("\n");
			continue;
		}
		int cnt4 = 0, cnt7 = 0;
		for(int i=1; i<=len; i++){
			if(str[i] < '4'){
				for(int j=0; j<mid-cnt4; j++)
					ans[i+j] = '4';
				for(int j=0; j<mid-cnt7; j++)
					ans[len-j] = '7';
				cnt4 = mid, cnt7 = mid;
				break;
			}
			else if(cnt4 < mid && str[i] == '4'){
				ans[i] = '4';
				cnt4++;
			}
			else if(cnt7 < mid && str[i] < '7'){
				ans[i] = '7';
				cnt7++;
				for(int j=0; j<mid-cnt4; j++)
					ans[i+j+1] = '4';
				for(int j=0; j<mid-cnt7; j++)
					ans[len-j] = '7';
				cnt4 = mid, cnt7 = mid;
				break;
			}
			else if(cnt7 < mid && str[i] == '7'){
				ans[i] = '7';
				cnt7++;
			}
			else{
				int p = i-1, flag = 0;
				for(;p;p--){
					if(ans[p] == '7') flag = 1;
					if(ans[p] == '4' && (flag || cnt7 < mid)) break;
				}
				if(!p){
					ans[1] = '7';
					cnt7 = 1, cnt4 = 0;
					for(int  j=1; j<=mid-cnt4; j++)
						ans[j+1] = '4';
					for(int j=0; j < mid-cnt7; j++)
						ans[len-j] = '7';
					break;					
				}
				ans[p] = '7';
				cnt4 = 0, cnt7 = 1;
				for(int j=1; j<p; j++){
					if(ans[j] != '4') cnt7++;
					else cnt4++;
				}
				for(int j=0; j < mid-cnt4; j++)
					ans[j+p+1] = '4';
				for(int j=0; j < mid - cnt7; j++)
					ans[len-j] = '7';
				cnt4 = mid, cnt7 = mid;
				break;
			}
		}
		for(int i=1; i<=len; i++)
			printf("%c", ans[i]);
		printf("\n");
	}
	return 0;
}