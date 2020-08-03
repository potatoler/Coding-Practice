#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#define int long long
using namespace std;
const int MaxN = 156005, Mod = 1e4+7;
struct Trie{
    int fail, son[26];
    bool available;
}trie[MaxN];
int cntTrie, n, m, f[110][MaxN], queue[MaxN], top;
char str[110];

inline int QuickPower(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1) ans = ans * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return ans;
}

inline void Insert(char str[], int length){
    int cur = 0;
    for(int i=1; i<=length; i++){
        int serial = str[i] - 'A';
        if(!trie[cur].son[serial]) trie[cur].son[serial] = ++cntTrie;
        cur = trie[cur].son[serial];
    }
    trie[cur].available = true;
}

inline void Build(){
    int p = 1; top = 0;
    for(int i=0; i<26; i++)
        if(trie[0].son[i]) queue[++top] = trie[0].son[i];
    while(p <= top){
        int cur = queue[p++];
        for(int i=0; i<26; i++)
            if(trie[cur].son[i]){
                trie[trie[cur].son[i]].fail = trie[trie[cur].fail].son[i];
                trie[trie[cur].son[i]].available |= trie[trie[trie[cur].son[i]].fail].available;
                queue[++top] = trie[cur].son[i];
            }
            else trie[cur].son[i] = trie[trie[cur].fail].son[i];
    }
}

signed main(){
    scanf("%lld%lld", &n, &m);
    for(int i=1; i<=n; i++){
        scanf("%s", str+1);
        Insert(str, strlen(str+1));
    }
    Build();
    f[0][0] = 1;
    for(int i=0; i<m; i++)
        for(int j=0; j<=cntTrie; j++)
            for(int k=0; k<26; k++)
                if(!trie[trie[j].son[k]].available) f[i+1][trie[j].son[k]] = (f[i+1][trie[j].son[k]] + f[i][j]) % Mod;
    int ans = QuickPower(26, m);
    for(int i=0; i<=cntTrie; i++)
        ans = (ans - f[m][i] + Mod) % Mod;
    printf("%lld\n", ans);
    return 0;
}