//AC?
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 300005;
int n, a[MaxN];
int mn[MaxN], mx[MaxN], bucket[MaxN*2], ans;

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

inline void Divide_and_Conquer(int l, int r){
    if(l == r) return (void)ans++;
    int mid = (l+r)/2;
    Divide_and_Conquer(l, mid);
    Divide_and_Conquer(mid+1, r);
    mx[mid] = mn[mid] = a[mid];
    mx[mid+1] = mn[mid+1] = a[mid+1];
    int i, j, k;
    // Initiate part: calcutale max and min value from middle to the two border.
    for(i = mid-1; i>=l; i--){
        mx[i] = max(mx[i+1], a[i]);
        mn[i] = min(mn[i+1], a[i]);
    }
    for(j = mid+2; j<=r; j++){
        mx[j] = max(mx[j-1], a[j]);
        mn[j] = min(mn[j-1], a[j]);
    }
    // If the max and min value are both on the left:
    for(i = mid; i>=l; i--){:q
		``
        j = mx[i] - mn[i] + i;
        if(j <= r && j > mid && mx[i] > mx[j] && mn[i] < mn[j]) ans++;
    }
    // If the max and min value are both on the right:
    for(j = mid+1; j<=r; j++){
        i = j - mx[j] + mn[j];
        if(i <= mid && i >= l && mx[j] > mx[i] && mn[j] < mn[i]) ans++;
    }
    // If the min value is on the left while the max value is on the right:
    // We should have "mn[i] - i == mx[j] - j" now.
    j = k = mid+1;
    for(i = mid; i>=l; i--){
        while(j <= r && mn[j] > mn[i]){
            bucket[mx[j]-j+n]++;
            j++;
        }
        // Why do we stop once mn[j] is not greater than mn[i]?
        // Because in this condition, mn[j] have been in the right part of segment, so the mn[j] will always less than mn[i].
        while(k < j && mx[k] < mx[i]){
            bucket[mx[k]-k+n]--;// By the way we'd better plus n to prevent mx[k]-k from being negative.
            k++;
        }
        ans += bucket[mn[i]-i+n];
    }
    // Reset bucket, j and k.
    while(k < j){
        bucket[mx[k]-k+n]--;
        k++;
    }
    i = k = mid;
    // If the min value is on the right while the max value is on the left:
    // We should have "mx[i] - i == mn[j] - j" now.
    for(j = mid+1; j<=r; j++){
        while(i >= l && mn[i] > mn[j]){
            bucket[mx[i]+i]++;
            i--;
        }
        while(k > i && mx[k] < mx[j]){
            bucket[mx[k]+k]--;
            k--;
        }
        ans += bucket[mn[j]+j];
    }
    // Reset again.
    while(k > i){
        bucket[mx[k]+k]--;
        k--;
    }
}

signed main(){
    n = Read();
    for(int i=1; i<=n; i++){
        int u = Read(), v = Read();
        a[u] = v;
    }
    Divide_and_Conquer(1, n);
    printf("%lld\n", ans);
    return 0;
}
