#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 30, P = 1e9 + 9;
int n, m, a[MAXN], x = 0;
char oplus;
long long ans = 0, fac[MAXN];

int op(int a, int b) {
    if (oplus == '&')
        return a & b;
    else if (oplus == '|')
        return a | b;
    else if (oplus == '^')
        return a ^ b;
    else
        return 0;
}

int identity() {
    if (oplus == '&')
        return (1 << m) - 1;
    else
        return 0;
}

void dfs(int k, int v, int c) {
    if (k == n) {
        if (v == x && c)
            ans = (ans + fac[c]) % P;
        return;
    }
    dfs(k + 1, op(v, a[k]), c + 1);
    dfs(k + 1, v, c);
}

int main() {
    scanf(" %c%d%d", &oplus, &n, &m);
    for (int i = 0; i < n; i++) {
        a[i] = 0;
        for (int j = 0; j < m; j++) {
            int bit;
            scanf("%d", &bit);
            a[i] = a[i] * 2 + bit;
        }
    }
    for (int i = 0; i < m; i++) {
        int bit;
        scanf("%d", &bit);
        x = x * 2 + bit;
    }
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) fac[i] = fac[i - 1] * i % P;
    dfs(0, identity(), 0);
    printf("%lld\n", ans);
}