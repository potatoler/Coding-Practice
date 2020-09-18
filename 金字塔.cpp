#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 302, Mod = 1000000000;
char s[MaxN];
int f[MaxN][MaxN];

inline int DFS(int l, int r){
    if(l == r) return 1;
    if(l > r) return 0;
    if(f[l][r] != -1) return f[l][r];
    f[l][r] = 0;
    for(int i=l+2; i<=r; i++)
        if(s[i] == s[l]) f[l][r] = (f[l][r] + DFS(l+1, i-1) * DFS(i, r)) % Mod;
    return f[l][r];
}
signed main(){
    scanf("%s", s);
    int length = strlen(s);
    memset(f, -1, sizeof(f));
    printf("%lld", DFS(0,length-1));
    return 0;
}