#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#include<utility>
#include<queue>
#define int long long 
using namespace std;
const int MaxN = 3000006;
int n, a[MaxN];
typedef pair<int,int> int_pair;
#define health first
#define serial second

class Set{
private:
	deque<int_pair> original, newsnake;
public:
	inline void Init(){
		original.clear();
		newsnake.clear();
		for(int i=1; i<=n; i++)
			original.push_back(make_pair(a[i],i));
		return;
	}
	
	inline int Size(){
		return original.size() + newsnake.size();
	}
	
	inline int_pair GetMin(){
		if(original.size()){
			if(newsnake.size()){
				return min(original.front(), newsnake.front());
			}
			return original.front();
		}
		return newsnake.front();
	}
	
	inline int_pair PopMin(){
		int_pair res;
		if(original.size()){
			if(newsnake.size()){
				if(original.front() < newsnake.front()){
					res = original.front();
					original.pop_front();
				}
				else{
					res = newsnake.front();
					newsnake.pop_front();
				}
			}
			else{
				res = original.front();
				original.pop_front();
			}
		}
		else{
			res = newsnake.front();
			newsnake.pop_front();
		}
		return res;
	}
	
	inline int_pair PopMax(){
		int_pair res;
		if(original.size()){
			if(newsnake.size()){
				if(original.back() > newsnake.back()){
					res = original.back();
					original.pop_back();
				}
				else{
					res = newsnake.back();
					newsnake.pop_back();
				}
			}
			else{
				res = original.back();
				original.pop_back();
			}
		}
		else{
			res = newsnake.back();
			newsnake.pop_back();
		}
		return res;
	}
	
	inline void Insert(int_pair x){
		newsnake.push_front(x);
		return;
	}
}set;

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

inline bool CanEat(){
	int_pair mn = set.PopMin(), mx = set.PopMax();
	mx.health -= mn.health;
	bool res = mx > set.GetMin();
	set.Insert(mx);
	return res;
}

inline bool End(){
	if(set.Size() == 1) return true;
	if(CanEat()) return false;
	return !End();
}

inline int Calculate(){
	if(n <= 2) return 1;
	for(int i=n; i>=4; i--){
		if(!CanEat()){
			if(End()) return i-1;
			return i;
		}
	}
	if(CanEat()) return 1;
	return 3;
}

signed main(){
	int T = Read();
	if(!T) return 0;
	n = Read();
	for(int i=1; i<=n; i++)
		a[i] = Read();
	set.Init();
	printf("%lld\n", Calculate());
	while(--T){
		int k = Read();
		for(int i=1; i<=k; i++){
			int x = Read(), y = Read();
			a[x] = y;
		}
		set.Init();
		printf("%lld\n", Calculate());
	}
	return 0;
}