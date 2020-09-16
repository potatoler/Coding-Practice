#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<stack>
#define int long long
using namespace std;
const int MaxN = 100000;
int n, ans;
char a[MaxN];
stack<char> st;

signed main(){
	scanf("%s", a);
	n = strlen(a);
	for(int i=0; i<n; i++){
		while(st.size())
			st.pop();
		for(int j=i; j<n; j++){
			if(a[j] == '(') st.push(')');
			else if(a[j] == '[') st.push(']');
			else if(a[j] == '{') st.push('}');
			else if(st.empty() || a[j] != st.top()) break;
			else{
				st.pop();
				if(st.empty()) ans = max(ans, j-i+1);
			}
		}
	}
	printf("%lld", ans);
}