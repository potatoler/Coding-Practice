#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;

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

inline int QuickMul(int a, int b, int mod){
    a %= mod, b %= mod;
    int ans = 0;
    while(b){
        if(b&1) ans = (ans + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

inline int QuickPow(int a, int b, int mod){
    int ans = 1;
    while(b){
        if(b&1) ans = QuickMul(ans, a, mod) % mod;
        a = QuickMul(a, a, mod) % mod;
        b >>= 1;
    }
    return ans;
}

inline int GCD(int a, int b){
    if(a < b) swap(a,b);
    if(!b) return a;
    return GCD(b, a%b);
}

inline int ExGCD(int a, int b, int &x, int &y){
    if(!b){
        x = a, y = 0;
        return a;
    }
    int ans = ExGCD(b, a%b, x, y);
    int t = x;
    x = y, y = t- a / b * y;
    return ans;
}

inline int PollardRho(int x, int c){
    int xi = 1ll * rand() * rand() % (x-1) + 1, y = xi, i = 1, k = 2;
    while(true){
        i++;
        xi = (QuickMul(xi, xi, x) + c) % x;
        int gcd = GCD(abs(y-xi) % x, x);
        if(gcd > 1 && gcd < x) return gcd;
        if(xi == y) return x;
        if(i == k){
            y = xi;
            k <<= 1;
        }
    }
    return x;
}

signed main(){
    srand(19260817);
    int e = Read(), N = Read(), c = Read();
    int p = N;
    while(p >= N)
        p = PollardRho(N, 1ll * rand() * rand() % (N-1) + 1);
    int r = (p-1) * (N/p-1);
    // printf("%lld %lld\n", p, N/p);
    int d, y;
    int tmp = ExGCD(e, r, d, y);
    d = (d % r + r) % r;
    int n = QuickPow(c, d, N);
    printf("%lld %lld", d, n);
    return 0;
}