#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#define int long long
using namespace std;
int n, solution[10][10];

class Mayan{
	public:
		
	int colour[10][10], height[10];
	
	inline void Move(int x, int y, int g){
		// Target position with a block
		if(height[x+g] <= y){
			colour[x+g][height[x+g]] = colour[x][y];
			height[x+g]++;
			for(int i=y+1; i<height[x]; i++)
				colour[x][i-1] = colour[x][i];
			height[x]--;
			colour[x][height[x]] = 0;
		}
		// Target position without a block
		else swap(colour[x+g][y], colour[x][y]);
	}
	
	inline bool One_Time_Erase(){// Return if any blocks will drop
		bool erase_any = false;
		bool tag[10][10];
		memset(tag, false, sizeof(tag));
		// Erase vertically
		for(int i=0; i<5; i++)
			for(int j=1; j<height[i]-1; j++)
				if(colour[i][j-1] == colour[i][j] && colour[i][j] == colour[i][j+1]) erase_any = tag[i][j-1] = tag[i][j] = tag[i][j+1] = true;
		// Erase horizontally
		for(int i=1; i<4; i++)
			for(int j=0; j<height[i]; j++)
				if(colour[i-1][j] == colour[i][j] && colour[i][j] == colour[i+1][j]) erase_any = tag[i-1][j] = tag[i][j] = tag[i+1][j] = true;
		if(!erase_any) return false;
		// Blocks drop
		for(int i=0; i<5; i++){
			int newHeight = 0;
			for(int j=0; j<height[i]; j++){
				if(!tag[i][j]){
					colour[i][newHeight] = colour[i][j];
					newHeight++;
					if(newHeight-1 != j) colour[i][j] = 0;
				}
				else colour[i][j] = 0;
			}
			height[i] = newHeight;
		}
		return true;
	}
	
	inline bool Judge(){
		return (!height[0] && !height[1] && !height[2] && !height[3] && !height[4]);
	}
	
	inline void Erase(){
		while(One_Time_Erase());
		return;
	}
	
}mayan;

inline void DFS(Mayan cur, int step){
	bool isClear = cur.Judge();
	if(step == n){
		if(isClear){
			for(int i=0; i<n; i++)
				printf("%lld %lld %lld\n", solution[i][0], solution[i][1], solution[i][2]);
			exit(0);
		}
		return;
	}
	for(int i=0; i<5; i++){
		for(int j=0; j<cur.height[i]; j++){
			if(i != 0){
				if(!cur.colour[i-1][j]){
					Mayan nxt = cur;
					nxt.Move(i, j, -1);
					solution[step][0] = i, solution[step][1] = j, solution[step][2] = -1;
					nxt.Erase();
					DFS(nxt, step+1);
				}
			}
			if(i != 4){
				if(cur.colour[i+1][j] != cur.colour[i][j]){
					Mayan nxt = cur;
					nxt.Move(i, j, 1);
					solution[step][0] = i, solution[step][1] = j, solution[step][2] = 1;
					nxt.Erase();
					DFS(nxt, step+1);
				}
			}
		}
	}
}

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

signed main(){
	n = Read();
	for (int i=0; i<5;i ++) {
		mayan.height[i] = 0;
		for (int &j=mayan.height[i]; true; j++){
			int tmp = Read();
            if (tmp == 0) break;
            if (j < 7) mayan.colour[i][j] = tmp;
        }
	}
	DFS(mayan, 0);
	printf("-1");
	return 0;
}