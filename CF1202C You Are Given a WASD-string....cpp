#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 200005;
char cmd[MaxN];
int row[MaxN], col[MaxN];

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

inline void umax(int &a, int b){
	a = max(a, b);
}

inline void umin(int &a, int b){
	a = min(a, b);
}

signed main(){
	int t = Read();
	while(t--){
		scanf("%s", cmd+1);
		int n = strlen(cmd+1), row_cnt = 0, col_cnt = 0;
		for(int i=1; i<=n; i++){
			if(cmd[i] == 'W') row[++row_cnt] = 1;
			else if(cmd[i] == 'S') row[++row_cnt] = -1;
			else if(cmd[i] == 'A') col[++col_cnt] = -1;
			else col[++col_cnt] = 1;
		}
		int minv = 0, maxv = 0, cur = 0, row_len, row_f, col_len, col_f;
		for(int i=1; i<=row_cnt; i++)
			cur += row[i], umax(maxv,cur), umin(minv,cur);
		row_f = row_len = maxv-minv+1;
		int tmpmin=0, tmpmax=0, flag=0;
		cur = 0;
		for(int i=1; i<=row_cnt; i++){
			cur += row[i];
			if(cur == maxv && !flag) flag = 1, cur--, umin(tmpmin,cur-1);
			umax(tmpmax,cur), umin(tmpmin,cur);
		}
		umin(row_f,tmpmax-tmpmin+1);
		tmpmin = 0, tmpmax = 0, flag = 0;
		cur = 0;
		for(int i=1; i<=row_cnt; i++){
			cur += row[i];
			if(cur == minv && !flag) flag=1, cur++, umax(tmpmax,cur+1);
			umax(tmpmax,cur),umin(tmpmin,cur);
		}
		umin(row_f, tmpmax-tmpmin+1);
		minv = maxv = 0; cur = 0;
		for(int i=1; i<=col_cnt; i++)
			cur += col[i], umax(maxv,cur), umin(minv,cur);
		col_f = col_len = maxv-minv+1;
		tmpmin = 0, tmpmax = 0, flag = 0;
		cur = 0;
		for(int i=1; i<=col_cnt; i++){
			cur += col[i];
			if(cur == maxv && !flag) flag = 1, cur--, umin(tmpmin,cur-1);
			umax(tmpmax,cur), umin(tmpmin,cur);
		}
		umin(col_f,tmpmax-tmpmin+1);
		tmpmin = 0, tmpmax = 0, flag = 0;
		cur = 0;
		for(int i=1; i<=col_cnt; i++){
			cur += col[i];
			if(cur == minv && !flag) flag = 1, cur++, umax(tmpmax,cur+1);
			umax(tmpmax,cur), umin(tmpmin,cur);
		}
		umin(col_f, tmpmax-tmpmin+1);
		printf("%lld\n", min(row_f*col_len,row_len*col_f));
	}
	return 0;
}