#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 5003;
int n, m, k;
int f[MaxN*2][MaxN], a[MaxN*2], s[MaxN*2][MaxN];

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

int main(){
    n = Read(), m = Read(), k = Read();
    for (int i = 1; i <= n; i++)
        a[i] = Read();
    int p = 1;
    for (int i = n + 1; i <= n + m; i++){
        if (p > n)
            p = 1;
        a[i] = a[p];
        p++;
    }
    for (int i = n + m - 1; i >= 1; i--){
        for (int j = m - 1; j >= 1; j--){
            if (a[i] == a[i + 1]){
                s[i][j] = s[i][j + 1];
                if (j + k < m)
                    s[i][j] -= f[i][j + k];
                if (s[i + 1][j + 1] > 0){
                    f[i][j] = 1;
                    s[i][j]++;
                }
            }
            else{
                s[i][j] = s[i][j + 1];
                if (j + k < m)
                    s[i][j] -= f[i][j + k];
                if (s[i + 1][j + 1] == 0){
                    f[i][j] = 1;
                    s[i][j]++;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            if (f[i][j]){
                printf("%d ", a[i]);
                break;
            }
            else if (j == k) printf("%d ", a[i] ^ 1);
    return 0;
}
