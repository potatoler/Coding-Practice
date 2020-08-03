#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<queue>
#define int long long
using namespace std;
const int MaxN = 1000005;
struct Trie{
    int fail, position[26], end;
}trie[MaxN];
struct Answer{
    int number, position;
}ans[MaxN];
int cntTrie, n;
string s[MaxN];

inline bool operator < (Answer a, Answer b){
    if(a.number != b.number) return a.number > b.number;
    else return a.position < b.position;
}

inline void Reset(int x){// Haruki, Reset!
    memset(trie[x].position, 0, sizeof(trie[x].position));
    trie[x].fail = trie[x].end = 0;
}

inline void Build(string s, int num){
    int len = s.length(), cur = 0;
    for(int i=0; i<len; i++){
        if(!trie[cur].position[s[i]-'a']){
            trie[cur].position[s[i]-'a'] = ++cntTrie;
            Reset(cntTrie);
        }
        cur = trie[cur].position[s[i]-'a'];
    }
    trie[cur].end = num;;
}

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
    }
}

inline void Query(string s){
    int len = s.length(), cur = 0;
    for(int i=0; i<len; i++){
        cur = trie[cur].position[s[i]-'a'];
        for(int t = cur; t; t = trie[t].fail){
            ans[trie[t].end].number++;
        }
    }
    return;
}

signed main(){
    while(1){
        scanf("%lld", &n);
        if(n == 0) break;
        Reset(0);
        for(int i=1; i<=n; i++){
            cin>>s[i];
            ans[i].number = 0;
            ans[i].position = i;
            Build(s[i], i);
        }
        trie[0].fail = 0;
        ConstructFail();
        cin>>s[0];
        Query(s[0]);
        sort(ans+1, ans+1+n);
        printf("%lld\n", ans[1].number);
        cout<<s[ans[1].position]<<endl;
        for(int i=2; i<=n; i++){
            if(ans[i].number == ans[i-1].number) cout<<s[ans[i].position]<<endl;
            else break;
        }
    }
    return 0;
}