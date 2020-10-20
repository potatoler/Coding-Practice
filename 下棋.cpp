#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;
int sg[102] = {0,1}, visited[102];

inline int Read(){
	int num = 0, opt = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') opt = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * opt;
}

inline int SG(int x){
	return x<=51? sg[x] : sg[51 + (x-51) % 34 + (!((x-51)%34)? 34 : 0)];
}

signed main(){
	for(int i=2; i<=85; i++){
		visited[sg[i-2]] = i;
		for(int j=0; j<=i-3; j++)
			visited[sg[j] ^ sg[i-3-j]] = i;
		int p=0;
		while(visited[p] == i) p++;
		sg[i] = p;
	}
	int t = Read();
	while(t--){
		int ans = 0, n = Read();
		while(n--) ans ^= SG(Read());
		puts(ans? "Alice" : "Bob");
	}
	return 0;
}