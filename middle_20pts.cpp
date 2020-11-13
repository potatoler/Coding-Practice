#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<vector>
#include<utility>
#include<set>
#define int long long
using namespace std;
int n;

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
	n = Read();
	vector<int> a(2*n-1);
	for(int i=0; i<2*n-1; i++)
		a[i] = Read();
	sort(a.begin(), a.end());
	set< vector<int> > ok;
	do{
		vector<int> b(n);
		for(int i=0; i<n; i++){
			vector<int> c;
			c.insert(c.end(), a.begin(), a.begin() + 2*i + 1);
			sort(c.begin(), c.end());
			b[i] = c[i];
		}
		ok.insert(b);
	}while(next_permutation(a.begin(), a.end()));
	printf("%lu", ok.size());
	return 0;
}