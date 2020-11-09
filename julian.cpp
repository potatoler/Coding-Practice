#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<climits>
#define int long long
using namespace std;
const int four = 365*3+366, hundred = four * 25 - 1, four_hundred = four * 100 - 3;;
int yyyy, mm, dd, month[13] = {29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool bc, leap, gr;

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

inline int Year(int x){
	if(x <= 1178 * four + 366){
		bc = true;
		if(x <= 366){
			yyyy = 4713;
			leap = true;
			return x;
		}
		else{
			x -= 366;
			yyyy = 4712;
			int turn = x / four;
			x = x % four;
			yyyy -= turn * 4;
			if(x == 0){
				leap = true;
				return x;
			}
			if(x > 365 * 3){
				yyyy -= 3;
				x -= 365 * 3;
				leap = true;
				return x;
			}
			else{
				int last = x / 365;
				x = x % 365;
				yyyy -= last;
				leap = false;
				return x;
			}
		}
	}
	else{
		bc = false;
		x -= (1178 * four + 366);
		if(x <= 395*four + 365 + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 4){
			yyyy = 1;
			gr = false;
			int trun = x / four;
			x = x % four;
			yyyy += trun * 4;
			if(x == 0){
				leap = true;
				return x;
			}
			if(x > 365 * 3){
				yyyy += 3;
				x -= 365 * 3;
				leap = true;
				return x;
			}
			else{
				int last = x / 365;
				x = x % 365;
				yyyy += last;
				leap = false;
				return x;
			}
		}
		else{
			gr = true;
			x -= (395*four + 365 + 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 4);
			if(x <= 17 + 30 + 31){
				yyyy = 1582;
				leap = false;
				return x;
			}
			else{
				x -= (17 + 30 + 31);
				if(x <= 365 + 366){
					if(x <= 365){
						yyyy = 1583;
						leap = false;
						return x;
					}
					else{
						x -= 365;
						yyyy = 1584;
						leap = true;
						return x;
					}
				}
				else{
					yyyy = 1585;
					x -= (365 + 366);
					if(x <= four * 4){
						int turn = x / four;
						x = x % four;
						yyyy += turn * 4;
						if(x == 0){
							leap = true;
							return x;
						}
						if(x > 365 * 3){
							yyyy += 3;
							x -= 365 * 3;
							leap = true;
							return x;
						}
						else{
							int last = x / 365;
							x = x % 365;
							yyyy += last;
							leap = false;
							return x;
						}
					}
					else{
						x -= (four * 4);
						yyyy = 1601;
						int cen = x / four_hundred;
						x = x % four_hundred;
						yyyy += cen * 400;
						if(x == 0){
							leap = true;
							return x;
						}
//						printf("%lld %lld\n", x, yyyy);
						else if(x > hundred * 3){
							yyyy += 300;
							x -= hundred * 3;
						}
						else{
							int last = x / hundred;
							yyyy += last * 100;
							x = x % hundred;
							if(x == 0){
								leap = false;
								return x;
							}
						}
//						printf("%lld %lld\n", x, yyyy);
						int turn = x / four;
						x = x % four;
						yyyy += turn * 4;
						if(x == 0){
							leap = true;
							return x;
						}
						if(x > 365 * 3){
							yyyy += 3;
							x -= 365 * 3;
							leap = true;
							return x;
						}
						else{
							int last = x / 365;
							x = x % 365;
							yyyy += last;
							leap = false;
							return x;
						}
					}
				}
			}
		}
	}
}

inline void Date(int x){
	if(x == 0){
		mm = 1;
		dd = 1;
		return;
	}
	else if(yyyy == 1582 && gr == true){
		if(x <= 17){
			mm = 10;
			dd = 15 + x;
		}
		else if(x <= 17 + 30){
			mm = 11;
			x -= 17;
			dd = 1 + x;
		}
		else{
			mm = 12;
			x -= 17 + 30;
			dd = 1 + x;
		}
		if(dd == month[mm]+1){
			mm += 1;
			dd = 1;
		}
		if(mm == 13){
			mm = 1;
			yyyy += 1;
//			if(yyyy == 0){
//				yyyy = 1;
//				bc = false;
//			}
		}
		return;
	}
	else{
		for(int i=1; i<=12; i++){
			if(leap == true && i==2){
				x -= month[0];
			}
			else x -= month[i];
			if(x < 0){
				if(leap == true && i==2){
					x += month[0];
				}
				else x += month[i];
				mm = i;
				dd = 1 + x;
				return;
			}
			else if(x == 0){
				mm = i+1;
				dd = 1;
				if(mm == 13){
					yyyy += 1;
					mm = 1;
//					if(yyyy == 0){
//						yyyy = 1;
//						bc = false;
//					}
				}
				return;
			}
		}
	}
}

signed main(){
//	freopen("julian.in", "r", stdin);
//	freopen("julian.out", "w", stdout);
	int T = Read();
	while(T--){
		bc = false, gr = false, leap = false;
		int r = Read();
		r = Year(r);
		if(yyyy == 0){
			yyyy = 1;
			bc = false;
		}
		if(gr && (yyyy % 100 == 0) && (yyyy % 400 != 0)) leap = false;
//		printf("%lld\n", r);
//		if(leap) printf("leap\n");
		Date(r);
		if(yyyy == 1582 && mm == 10 && dd == 5) dd = 15;
		printf("%lld %lld %lld", dd, mm, yyyy);
		if(bc) printf(" BC\n");
		else printf("\n");
	}
	return 0;
}