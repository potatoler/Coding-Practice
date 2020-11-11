#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<set>
#include<vector>
#include<utility>
#include<map>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, k, sx, sy, sd;
char str[5];

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

struct Record{
	int x, y, d;
	bool operator != (const Record &b) const{
		return (x != b.x || y != b.y || d != b.d);
	}
};

class Block{
	private:
	set<int> storage[2][MaxN*2];
	
	public:
	inline int Serial(int x, int y, int dir){
		if(dir == 0) return x - y + m + 1;
		else return x + y;
	}
	
	inline void Insert(int x, int y){
		storage[0][Serial(x,y,0)].insert(x);
		storage[1][Serial(x,y,1)].insert(x);
		return;
	}
	
	inline set<int>::iterator Find(int dir, Record tar){
		return storage[dir][Serial(tar.x, tar.y, dir)].lower_bound(tar.x);
	}
};

class Grid{
	private:
	map< pair<int, int>, bool > mp;
	Block block;
	
	public:
	int ans;
	#define Serial(x,y) make_pair(x,y)
	
	inline void AddBlock(int x, int y){
		block.Insert(x,y);
		mp[Serial(x,y)] = true;
	}
	
	inline bool IfBlock(int x, int y){
		return mp[Serial(x,y)];
	}
	
	inline pair<Record,int> DFS(Record cur){
		Record rec;
		set<int> :: iterator it;
		switch(cur.d){
			case 1:{
				it = block.Find(0, cur);
				it--;
				rec.x = cur.x - (abs(*it - cur.x) - 1);
				rec.y = cur.y - (abs(*it - cur.x) - 1);
				if(IfBlock(rec.x-1, rec.y) && IfBlock(rec.x, rec.y-1)) rec.d = 3;
				else if(IfBlock(rec.x-1, rec.y)){
					rec.y--;
					rec.d = 4;
				}
				else if(IfBlock(rec.x, rec.y-1)){
					rec.x--;
					rec.d = 2;
				}
				else rec.d = 3;
				break;
			}
			case 2:{
				it = block.Find(1, cur);
				it--;
				rec.x = cur.x - (abs(*it - cur.x) - 1);
				rec.y = cur.y + (abs(*it - cur.x) - 1);
				if(IfBlock(rec.x-1, rec.y) && IfBlock(rec.x, rec.y+1)) rec.d = 4;
				else if(IfBlock(rec.x-1, rec.y)){
					rec.y++;
					rec.d = 3;
				}
				else if(IfBlock(rec.x, rec.y+1)){
					rec.x--;
					rec.d = 1;
				}
				else rec.d = 4;
				break;
			}
			case 3:{
				it = block.Find(0, cur);
				rec.x = cur.x + (abs(*it - cur.x) - 1);
				rec.y = cur.y + (abs(*it - cur.x) - 1);
//				printf("%lld %lld %lld %lld\n", cur.x, cur.y, rec.x, rec.y);
				if(IfBlock(rec.x+1, rec.y) && IfBlock(rec.x, rec.y+1)) rec.d = 1;
				else if(IfBlock(rec.x+1, rec.y)){
					rec.y++;
					rec.d = 2;
				}
				else if(IfBlock(rec.x, rec.y+1)){
					rec.x++;
					rec.d = 4;
				}
				else rec.d = 1;
				break;
			}
			case 4:{
				it = block.Find(1, cur);
				rec.x = cur.x + (abs(*it - cur.x) - 1);
				rec.y = cur.y - (abs(*it - cur.x) - 1);
				if(IfBlock(rec.x+1, rec.y) && IfBlock(rec.x, rec.y-1)) rec.d = 2;
				else if(IfBlock(rec.x+1, rec.y)){
					rec.y--;
					rec.d = 1;
				}
				else if(IfBlock(rec.x, rec.y-1)){
					rec.x++;
					rec.d = 3;
				}
				else rec.d = 2;
				break;
			}
		}
//		printf("%lld ", rec.d);
		return make_pair(rec, abs(*it - cur.x));
	}
	
	inline bool Judge(Record cur){
		Record rec = cur;
		do{
			pair<Record,int> tmp = DFS(cur);
			ans += tmp.second;
//			printf("%lld %lld %lld\n", tmp.first.x, tmp.first.y, tmp.first.d);
			switch(tmp.first.d){
				case 1:{
					if(cur.d == 3) return false;
					break;
				}
				case 2:{
					if(cur.d == 4) return false;
					break;
				}
				case 3:{
					if(cur.d == 1) return false;
					break;
				}
				case 4:{
					if(cur.d == 2) return false;
				}
			}
			cur = tmp.first;
		}while(rec != cur);
		return true;
	}
}grid;

signed main(){
	n = Read(), m = Read(), k = Read();
	for(int i=0; i<=m+1; i++){
		grid.AddBlock(0,i);
		grid.AddBlock(n+1,i);
	}
	for(int i=1; i<=n; i++){
		grid.AddBlock(i,0);
		grid.AddBlock(i,m+1);
	}
	for(int i=1; i<=k; i++){
		int x = Read(), y = Read();
		grid.AddBlock(x,y);
	}
	sx = Read(), sy = Read();
	scanf("%s", str+1);
	if(str[1] == 'N'){
		if(str[2] == 'W') sd = 1;
		else sd = 2;
	}
	else{
		if(str[2] == 'W') sd = 4;
		else sd = 3;
	}
	Record st = (Record){sx, sy, sd};
//	printf("%lld\n", sd);
	st = grid.DFS(st).first;
	if(!grid.Judge(st)){
		grid.ans--;
		switch(st.d){
			case 1:{
				st.d = 3;
				break;
			}
			case 2:{
				st.d = 4;
				break;
			}
			case 3:{
				st.d = 1;
				break;
			}
			case 4:{
				st.d = 2;
				break;
			}
		}
		grid.Judge(st);
	}
	printf("%lld", grid.ans);
	return 0;
}