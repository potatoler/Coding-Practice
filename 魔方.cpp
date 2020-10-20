#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;
int cube[7][4][4], tmp[7][4][4];
char op[100005];

inline int Read(){
	int num = 0, opt = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') opt = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * opt;
}

inline void Input(){
	for(int i=1; i<=3; i++)
		for(int j=1; j<=3; j++)
			cube[1][i][j] = Read();
	for(int i=1; i<=3; i++)
		for(int j=2; j<=4; j++)
			for(int k=1; k<=3; k++)
				cube[j][i][k] = Read();
	for(int i=1; i<=3; i++)
		for(int j=1; j<=3; j++)
			cube[5][i][j] = Read();
	for(int i=1; i<=3; i++)
		for(int j=1; j<=3; j++)
			cube[6][i][j] = Read();
	scanf("%s", op+1);
	return;
}

inline void OutPut(){
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++)
			printf("%d ", cube[1][i][j]);
		printf("\n");
	}
	for(int i=1; i<=3; i++){
		for(int j=2; j<=4; j++)
			for(int k=1; k<=3; k++)
				printf("%d ", cube[j][i][k]);
		printf("\n");
	}
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++)
			printf("%d ", cube[5][i][j]);
		printf("\n");
	}
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++)
			printf("%d ", cube[6][i][j]);
		printf("\n");
	}
	return;
}

signed main(){
//	freopen("cube.in", "r", stdin);
//	freopen("cube.out", "w", stdout);
	Input();
	int len = strlen(op+1);
	for(int a=1; a<=len; a++){
		memcpy(tmp, cube, sizeof(cube));
		if(op[a] == 'a'){
			for(int i=1; i<=3; i++)
				cube[1][i][1] = tmp[3][i][1],
				cube[3][i][1] = tmp[5][i][1],
				cube[5][i][1] = tmp[6][i][1],
				cube[6][i][1] = tmp[1][i][1];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[2][i][j] = tmp[2][j][4-i];
		}
		else if(op[a] == 'A'){
			for(int i=1; i<=3; i++)
				cube[1][i][1] = tmp[6][i][1],
				cube[3][i][1] = tmp[1][i][1],
				cube[5][i][1] = tmp[3][i][1],
				cube[6][i][1] = tmp[5][i][1];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[2][i][j] = tmp[2][4-j][i];			
		}
		else if(op[a] == 'b'){
			for(int i=1;i<=3;i++)
				cube[1][i][2] = tmp[3][i][2],
				cube[3][i][2] = tmp[5][i][2],
				cube[5][i][2] = tmp[6][i][2],
				cube[6][i][2] = tmp[1][i][2];
		}
		else if(op[a] == 'B'){
			for(int i=1; i<=3; i++)
				cube[1][i][2] = tmp[6][i][2],
				cube[3][i][2] = tmp[1][i][2],
				cube[5][i][2] = tmp[3][i][2],
				cube[6][i][2] = tmp[5][i][2];			
		}
		else if(op[a] == 'c'){
			for(int i=1; i<=3; i++)
				cube[1][i][3] = tmp[3][i][3],
				cube[3][i][3] = tmp[5][i][3],
				cube[5][i][3] = tmp[6][i][3],
				cube[6][i][3] = tmp[1][i][3];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[4][i][j] = tmp[4][4-j][i];
		}
		else if(op[a] == 'C'){
			for(int i=1; i<=3; i++)
				cube[1][i][3] = tmp[6][i][3],
				cube[3][i][3] = tmp[1][i][3],
				cube[5][i][3] = tmp[3][i][3],
				cube[6][i][3] = tmp[5][i][3];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[4][i][j] = tmp[4][j][4-i];			
		}
		else if(op[a] == 'd'){
			for(int i=1; i<=3; i++)
				cube[1][3][i] = tmp[4][i][1],
				cube[2][i][3] = tmp[1][3][4-i],
				cube[4][i][1] = tmp[5][1][4-i],
				cube[5][1][i] = tmp[2][i][3];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[3][i][j] = tmp[3][j][4-i];
		}
		else if(op[a] == 'D'){
			for(int i=1; i<=3; i++)
				cube[1][3][i] = tmp[2][4-i][3],
				cube[2][i][3] = tmp[5][1][i],
				cube[4][i][1] = tmp[1][3][i],
				cube[5][1][i] = tmp[4][4-i][1];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[3][i][j] = tmp[3][4-j][i];			
		}
		else if(op[a] == 'e'){
			for(int i=1; i<=3; i++)
				cube[1][2][i] = tmp[4][i][2],
				cube[2][i][2] = tmp[1][2][4-i],
				cube[4][i][2] = tmp[5][2][4-i],
				cube[5][2][i] = tmp[2][i][2];
		}
		else if(op[a] == 'E'){
			for(int i=1; i<=3; i++)
				cube[1][2][i] = tmp[2][4-i][2],
				cube[2][i][2] = tmp[5][2][i],
				cube[4][i][2] = tmp[1][2][i],
				cube[5][2][i] = tmp[4][4-i][2];
		}
		else if(op[a] == 'f'){
			for(int i=1; i<=3; i++)
				cube[1][1][i] = tmp[4][i][3],
				cube[2][i][1] = tmp[1][1][4-i],
				cube[4][i][3] = tmp[5][3][4-i],
				cube[5][3][i] = tmp[2][i][1];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[6][i][j] = tmp[6][4-j][i];
		}
		else if(op[a] == 'F'){
			for(int i=1; i<=3; i++)
				cube[1][1][i] = tmp[2][4-i][1],
				cube[2][i][1] = tmp[5][3][i],
				cube[4][i][3] = tmp[1][1][i],
				cube[5][3][i] = tmp[4][4-i][3];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[6][i][j] = tmp[6][j][4-i];
		}
		else if(op[a] == 'h'){
			for(int i=1; i<=3; i++)
				cube[2][1][i] = tmp[6][3][4-i],
				cube[3][1][i] = tmp[2][1][i],
				cube[4][1][i] = tmp[3][1][i],
				cube[6][3][i] = tmp[4][1][4-i];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[1][i][j] = tmp[1][j][4-i];
		}
		else if(op[a] == 'H'){
			for(int i=1; i<=3; i++)
				cube[2][1][i] = tmp[3][1][i],
				cube[3][1][i] = tmp[4][1][i],
				cube[4][1][i] = tmp[6][3][4-i],
				cube[6][3][i] = tmp[2][1][4-i];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[1][i][j] = tmp[1][4-j][i];
		}
		else if(op[a] == 'i'){
			for(int i=1; i<=3; i++)
				cube[2][2][i] = tmp[6][2][4-i],
				cube[3][2][i] = tmp[2][2][i],
				cube[4][2][i] = tmp[3][2][i],
				cube[6][2][i] = tmp[4][2][4-i];		
		}
		else if(op[a] == 'I'){
			for(int i=1; i<=3; i++)
				cube[2][2][i] = tmp[3][2][i],
				cube[3][2][i] = tmp[4][2][i],
				cube[4][2][i] = tmp[6][2][4-i],
				cube[6][2][i] = tmp[2][2][4-i];
		}
		else if(op[a] == 'j'){
			for(int i=1; i<=3; i++)
				cube[2][3][i] = tmp[6][1][4-i],
				cube[3][3][i] = tmp[2][3][i],
				cube[4][3][i] = tmp[3][3][i],
				cube[6][1][i] = tmp[4][3][4-i];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[5][i][j] = tmp[5][4-j][i];	
		}
		else if(op[a] == 'J'){
			for(int i=1; i<=3; i++)
				cube[2][3][i] = tmp[3][3][i],
				cube[3][3][i] = tmp[4][3][i],
				cube[4][3][i] = tmp[6][1][4-i],
				cube[6][1][i] = tmp[2][3][4-i];
			for(int i=1; i<=3; i++)
				for(int j=1; j<=3; j++)
					cube[5][i][j] = tmp[5][j][4-i];
		}
	}
	OutPut();
	return 0;
}