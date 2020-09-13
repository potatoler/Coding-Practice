#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<stack>
#define int long long
using namespace std;
const int MaxN = 1000006;
int score;
char str[MaxN];
stack<char> s;

signed main(){
	scanf("%s", str);
	int len = strlen(str);
	for(int i=0; i<len; i++){
		if(s.empty() || str[i]!=s.top()) s.push(str[i]);
		else score += 10, s.pop();
	}
	score += s.size()/2 * 5;
	printf("%lld", score);
}