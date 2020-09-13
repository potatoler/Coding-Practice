#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 102;
int f[MaxN][MaxN], lena, lenb;
int loca[30][MaxN], locb[30][MaxN];
char a[MaxN], b[MaxN];
vector<string> ans;

inline void PrintWay(int i, int j, int rest, string cur){
	if(!rest){
		ans.push_back(cur);
		return;
	}
	if(!i || !j) return;
	for(int k=0; k<26; k++){
		int posi = loca[k][i], posj = locb[k][j];
		if(f[posi][posj] == rest) PrintWay(posi-1, posj-1, rest-1, char('a'+k) + cur);
	}
}


signed main(){
	int T;
	scanf("%lld", &T);
	while(T--){
		memset(f, 0, sizeof(f));
		ans.clear();
		scanf("%s%s", a+1, b+1);
		lena = strlen(a+1), lenb = strlen(b+1);
		f[0][0] = 0;
		for(int i=1; i<=lena; i++)
			for(int j=1; j<=lenb; j++){
				int cur = max(f[i-1][j], f[i][j-1]);
				if(a[i] == b[j]) cur = f[i-1][j-1]+1;
				f[i][j] = cur;
			}
		for(int i=1; i<=lena; i++)
			for(int j=0; j<26; j++)
				if(a[i] == 'a'+j) loca[j][i] = i;
				else loca[j][i] = loca[j][i-1];
		for(int i=1; i<=lenb; i++)
			for(int j=0; j<26; j++)
				if(b[i] == 'a'+j) locb[j][i] = i;
				else locb[j][i] = locb[j][i-1];
		PrintWay(lena, lenb, f[lena][lenb], "");
		sort(ans.begin(), ans.end());
		for(int i=0; i<ans.size(); i++)
			cout<<ans[i]<<endl;
	}
	return 0;
}