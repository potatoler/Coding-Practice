#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#include<stack>
#define int long long
using namespace std;
const int MaxN = 1000006, MaxL = 2000006;
struct Trie{
    int fail, position[26], end;
}trie[MaxN];
int cntTrie, n, link[MaxN], size[MaxN], length[MaxN];
char s[MaxL], m[MaxL];

inline void Reset(int x){// Haruki, Reset!
    memset(trie[x].position, 0, sizeof(trie[x].position));
    trie[x].fail = trie[x].end = 0;
}

inline void Build(int serial){
    int len = length[serial], cur = 0;
    for(int i=0; i<len; i++){
        if(!trie[cur].position[s[i]-'a']){
            trie[cur].position[s[i]-'a'] = ++cntTrie;
            Reset(cntTrie);
        }
        cur = trie[cur].position[s[i]-'a'];
    }
    link[serial] = cur;
    return;
}

stack<int> st;
inline void ConstructFail(){
    queue<int> q;
    for(int i=0; i<26; i++){
        if(trie[0].position[i]){
            trie[trie[0].position[i]].fail = 0;
            q.push(trie[0].position[i]);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0; i<26; i++){
            if(trie[u].position[i]){
                trie[trie[u].position[i]].fail = trie[trie[u].fail].position[i];
                q.push(trie[u].position[i]);
            }
            else trie[u].position[i] = trie[trie[u].fail].position[i];
        }
        st.push(u);
    }
}

inline void Query(){
    int len = strlen(m), cur = 0;
    for(int i=0; i<len; i++){
        cur = trie[cur].position[m[i]-'a'];
        size[cur]++;
    }
    cur = 0;
    while(!st.empty()){
        cur = st.top();
        st.pop();
        size[trie[cur].fail] += size[cur];
    }
    return;
}

signed main(){
    scanf("%lld", &n);
    for(int i=1;i<=n;i++){
        scanf("%s", s);
        length[i] = strlen(s);
        Build(i);
    }
    scanf("%s", m);
    ConstructFail();
    Query();
    // for(int i=0;i<=n;i++)
    //     printf("%lld ", link[i]);
    // printf("\n");
    for(int i=1;i<=n;i++)
        printf("%lld\n", size[link[i]]);
    return 0;
}