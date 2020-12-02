#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int MaxN = 1000006;
int n, k, a[MaxN], ans;

inline int Read(){
    int num = 0, op = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-')  op = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num * op;
}

inline int Check(int x){
    int head = 1, tail = 1, sum = 0, cnt = 0;
    ans = 0;
    while(head <= n){
        while(tail < head && x < a[head] - a[tail])
            sum -= a[tail++];
        cnt += head - tail;
        ans += a[head] * (head-tail) - sum;
        sum += a[head];
        head++;
    }
    return cnt;
}

signed main(){
//    freopen("mark.in", "r", stdin);
//    freopen("mark.out", "w", stdout);
    n = Read(), k = Read();
    for(int i=1; i<=n; i++)
        a[i] = Read();
    sort(a+1, a+1+n);
    int l = 0, r = a[n]-a[1], res = 0;
    while(l <= r){
        int mid = (l+r) >> 1;
        if(Check(mid) >= k){
            res = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    int tmp = Check(res-1);
    ans += res * (k-tmp);
    printf("%lld", ans);
    return 0;
}