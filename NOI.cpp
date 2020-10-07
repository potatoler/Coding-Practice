#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
int a, b, c, d, e, f, g, h, i, score;
signed main(){
	scanf("%d%d%d%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f, &g, &h, &i);
	score = a + b + c + d + e + f + g + 50;
	if(h == 1) score += 5;
	if(score >= i) printf("AKIOI");
	else printf("AFO");
	return 0;
}