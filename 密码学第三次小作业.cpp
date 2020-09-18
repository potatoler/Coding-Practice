#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int __int128
using namespace std;
int n, c1, c2, e1, e2;

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

inline void Write(int x) {
    if (x > 9)
        Write(x / 10);
    putchar(x % 10 ^ '0');
}

inline int QuickMul(int a, int b, int mod){
    // int ans = 0;
    // while(b>0){
    //     if(b&1) ans = (ans + a) % mod;
    //     a = (a + a) % mod;
    //     b >>= 1;
    // }
    // return ans;
    a %= mod;
    b %= mod;
    return a*b%mod;
}

inline int QuickPower(int a, int b, int mod){
    int ans = 1;
    while(b>0){
        if(b&1) ans = QuickMul(ans,a,mod) % mod;
        a = QuickMul(a,a,mod) % mod;
        b >>= 1;
    }
    return ans;
}

inline int ExGCD(int a, int b, int &x, int &y){
    if(!b){
        x = 1, y = 0;
        return a;
    }
    int k = ExGCD(b, a%b, x, y);
    int z = x;
    x = y, y = z-a/b*y;
    return k;
}

inline int Inv(int a, int b){
    int x, y;
    int g = ExGCD(a, b, x, y);
    return g==1? (x%b+b)%b : -1;
}

signed main(){
    int T = Read();
    while(T--){
        c1 = Read(), c2 = Read(), e1 = Read(), e2 = Read(), n = Read();
        int a, b, g = ExGCD(e1, e2, a, b);
        if(a<0) c1 = Inv(c1, n), a = -a;
        if(b<0) c2 = Inv(c2, n), b = -b;
        int ans = QuickMul(QuickPower(c1,a,n), QuickPower(c2,b,n), n);
        // printf("%lld\n", ans);
        Write(ans);
        printf("\n");
    }
    return 0;
}