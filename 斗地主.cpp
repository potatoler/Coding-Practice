#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int T, n, ans, number[25];

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

inline void DFS(int x){
	if(x >= ans) return;
	
	// Single-card Straight:
	int length = 0;
	for(int i=3; i<=14; i++){
		if(number[i] == 0) length = 0;
		else{
			length++;
			if(length >= 5){
				for(int j=i; j>=i-length+1; j--)
					number[j]--;
				DFS(x+1);
				for(int j=i; j>=i-length+1; j--)
					number[j]++;
			}
		}
	}

	// Double-card Straight:
	length = 0;
	for(int i=3; i<=14; i++){
		if(number[i] <= 1) length = 0;
		else{
			length++;
			if(length >= 3){
				for(int j=i; j>=i-length+1; j--)
					number[j] -= 2;
				DFS(x+1);
				for(int j=i; j>=i-length+1; j--)
					number[j] += 2;
			}
		}
	}
	
	// Triple-card Straight:
	length = 0;
	for(int i=3; i<=14; i++){
		if(number[i] <= 2) length = 0;
		else{
			length++;
			if(length >= 2){
				for(int j=i; j>=i-length+1; j--)
					number[j] -= 3;
				DFS(x+1);
				for(int j=i; j>=i-length+1; j--)
					number[j] += 3;
			}
		}
	}
	
	// Along-with Pair:
	for(int i=2; i<=14; i++){
		if(number[i] <= 3){ // only 3 alone with some
			if(number[i] <= 2) continue;
			number[i] -= 3;
			for(int j=2; j<=15; j++){ // 3 alone with 1
				if(number[j] <= 0 || j == i) continue;
				number[j]--;
				DFS(x+1);
				number[j]++;
			}
			for(int j=2; j<=14; j++){ // 3 alone with 2
				if(number[j] <= 1 || j == i) continue;
				number[j] -= 2;
				DFS(x+1);
				number[j] += 2;
			}
			number[i] += 3;
		}
		else{ // 3 alone with some or 4 alone with some
			// 3 alone with some
			number[i] -= 3;
			for(int j=2; j<=15; j++){ // 3 alone with 1
				if(number[j] <= 0 || j == i) continue;
				number[j]--;
				DFS(x+1);
				number[j]++;
			}
			for(int j=2; j<=14; j++){ // 3 alone with 2
				if(number[j] <= 1 || j == i) continue;
				number[j] -= 2;
				DFS(x+1);
				number[j] += 2;
			}
			number[i] += 3;
			// 4 alone with some
			number[i] -= 4;
			for(int j=2; j<=15; j++){// 4 alone with 2 single
				if(number[j] <= 0 || j == i) continue;
				number[j]--;
				for(int k=2; k<=15; k++){
					if(number[k] <= 0 || j == k) continue;
					number[k]--;
					DFS(x+1);
					number[k]++;
				}
				number[j]++;
			}
			for(int j=2; j<=14; j++){// 4 alone with 2 couples
				if(number[j] <= 1 || j == i) continue;
				number[j] -= 2;
				for(int k=2; k<=14; k++){
					if(number[k] <= 1 || j == k) continue;
					number[k] -= 2;
					DFS(x+1);
					number[k] += 2;
				}
				number[j] += 2;
			}
			number[i] += 4;
		}
	}
	
	// Cards left:
	for(int i=2; i<=15; i++)
		if(number[i]) x++;
	ans = min(ans, x);
}

signed main(){
	T = Read(), n = Read();
	while(T--){
		ans = INT_MAX;
		memset(number, 0, sizeof(number));
		for(int i=1; i<=n; i++){
			int x = Read(), y = Read();
			if(x == 0) number[15]++;
			else if(x == 1) number[14]++;
			else number[x]++;
		}
		DFS(0);
		printf("%lld\n", ans);
	}
}