#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
const int MaxN = 200;
string str;
int have[MaxN], sum[MaxN], t, answer[MaxN*30];

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

inline int Transform(string stri){
	int res = stri[0] - '1';
	if(stri[1] == 'm') res += 0;
	else if(stri[1] == 'p') res += 9;
	else if(stri[1] == 's') res += 18;
	return res;
}

inline bool cmp(int a, int b){
	int anum = a%9+1, bnum = a%9+1;
	int acha = a / 9, bcha = b / 9;
	if(acha == bcha) return anum < bnum;
	else return acha < bcha;
}

inline bool Mianzi(){
	int cnt = 0, tmp[35];
	for(int i=0; i<27; i++)
		tmp[i] = sum[i];
	for(int i=0; i<=18; i+=9){
		for(int j=0; j<9; j++){
			if(tmp[i+j]>=3){
				tmp[i+j] -= 3;
				cnt++;
			}
			while(j+2 < 9 && tmp[i+j] && tmp[i+j+1] && tmp[i+j+2]){
				tmp[i+j]--;
				tmp[i+j+1]--;
				tmp[i+j+2]--;
				cnt++;
			}
		}
	}
	if(cnt==4)return true;
	return false;
}

inline bool Quetou(){
	for(int i=0; i<27; i++){
		if(sum[i] >= 2){
			sum[i] -= 2;
			if(Mianzi()){
				sum[i] += 2;
				return true;
			}
			sum[i] += 2;
		}
	}
	return false;
}

inline bool Check(){
	for (int i=0; i<=26; i++)
		if(sum[i] > 4) return false;
	if(Quetou()) return true;
	return false;
}

signed main(){
//	freopen("mahjong.in", "r", stdin);
//	freopen("mahjong.out", "w", stdout);
	int op = Read(), T = Read();
	while (T--){
		t++;
		memset(sum, 0, sizeof(sum));
		memset(answer, 0, sizeof(answer));
		int ans = 0, target = 0;
		
		if(op == 13){
			for (int i=1; i<=13; i++){
				cin >> str;
				have[i] = Transform(str);
				sum[have[i]]++;
			}
		}
		else{
			for (int i=1; i<=13; i++){
				cin >> str;
				have[i] = Transform(str);
				sum[have[i]]++;
			}
			cin >> str;
			target = Transform(str);
		}
		
		for (int i=0; i<=26; i++){
			have[14] = i;
			sum[have[14]] ++;
			if(Check()){
				ans++;
				answer[ans] = i;
			}
			sum[have[14]]--;
		}
		
		if(op == 13){
			if(ans){
				sort(answer+1, answer+1+ans, cmp);
				for (int i=1; i<=ans; i++){
					printf("%d",(answer[i]%9)+1);
					if (answer[i] / 9 == 0) printf("m ");
					else if(answer[i] / 9 == 1) printf("p ");
					else if(answer[i] / 9 == 2) printf("s ");
				}
				printf("\n");
			}
			else printf("\n");
		}
		else{
			int hu = false;
			for (int i=1; i<=ans; i++){
				if(answer[i] == target){
					hu = true;
					break;
				}
			}
			if(hu) printf("1\n");
			else printf("0\n");
		}
	}
	return 0;
}