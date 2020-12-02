#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>
#define int long long
using namespace std;
const int MaxN = 500005;
int n, m, f[MaxN * 3][4], cnt1, cnt2, cnt3;
struct Item {
    int p, w;
    bool operator<(const Item &y) const { return p > y.p; }
} item1[MaxN], item2[MaxN], item3[MaxN];

inline int Read() {
    int num = 0, op = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            op = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num * op;
}

signed main() {
    n = Read(), m = Read();
    for (int i = 1; i <= n; i++) {
        int w = Read();
        switch (w) {
            case 1: {
                cnt1++;
                item1[cnt1].w = w;
                item1[cnt1].p = Read();
                break;
            }
            case 2: {
                cnt2++;
                item2[cnt2].w = w;
                item2[cnt2].p = Read();
                break;
            }
            case 3: {
                cnt3++;
                item3[cnt3].w = w;
                item3[cnt3].p = Read();
                break;
            }
        }
    }
    sort(item1 + 1, item1 + 1 + cnt1);
    sort(item2 + 1, item2 + 1 + cnt2);
    sort(item3 + 1, item3 + 1 + cnt3);
    for (int i = 1; i <= m*2; i++) {
        if (f[i - 1][0] + item1[f[i - 1][1] + 1].p >= f[i][0]) {
            f[i][0] = f[i - 1][0] + item1[f[i - 1][1] + 1].p;
            f[i][1] = f[i - 1][1] + 1;
            f[i][2] = f[i - 1][2];
            f[i][3] = f[i - 1][3];
        }
        if (i > 1 && f[i - 2][0] + item2[f[i - 2][2] + 1].p >= f[i][0]) {
            f[i][0] = f[i - 2][0] + item2[f[i - 2][2] + 1].p;
            f[i][1] = f[i - 2][1];
            f[i][2] = f[i - 2][2] + 1;
            f[i][3] = f[i - 2][3];
        }
        if (i > 2 && f[i - 3][0] + item3[f[i - 3][3] + 1].p >= f[i][0]) {
            f[i][0] = f[i - 3][0] + item3[f[i - 3][3] + 1].p;
            f[i][1] = f[i - 3][1];
            f[i][2] = f[i - 3][2];
            f[i][3] = f[i - 3][3] + 1;
        }
    }
    printf("%lld", f[m][0]);
    return 0;
}