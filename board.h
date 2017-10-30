#include <array>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

class board {

public:
	board() : tile() {}
	board(const board &b) = default;
	board& operator = (const board &b) = default;

	std::array<int,15>& operator [] (const int &i) { return tile[i]; }
	const std::array<int,15>& operator [] (const int &i) const { return tile[i]; }
	int& operator () (const int &i) { return tile[i/15][i%15]; }
	const int& operator () (const int &i) const { return tile[i/15][i%15]; }

public:
	bool operator == (const board& b) const { return tile == b.tile; }
	bool operator <  (const board& b) const { return tile <  b.tile; }
	bool operator != (const board& b) const { return !(*this == b); }
	bool operator >  (const board& b) const { return b < *this; }
	bool operator <= (const board& b) const { return !(b < *this); }
	bool operator >= (const board& b) const { return !(*this < b); }

public:
	void getHead(int &x, int &y){
		x = y = 0;
		for (int r=0; r<15; r++){
			for (int c=0; c<15; c++){
				if (tile[r][c] > tile[x][y])x=r, y=c;
			}
		}
	}
	bool getFruit(int &x, int &y){
		for (int r=0; r<15; r++){
			for (int c=0; c<15; c++){
				if (tile[r][c]==-1){
					x=r, y=c;
					return 1;
				}
			}
		}
		return 0;
	}
	bool genFruit(){
		int x, y;
		if ( getFruit(x,y)==1 )return 1;

		std::vector<int> pos(15*15);
		for (int i=0; i<15*15; i++) pos[i] = i;
		std::random_shuffle(pos.begin(),pos.end());

		for (int idx:pos){
			if (tile[idx/15][idx%15]==0){
				tile[idx/15][idx%15] = -1;
				return 1;
			}
		}
		return 0;
	}
	int move(const int &opcode){
		const int dx[4] = {1,0,-1,0};
		const int dy[4] = {0,1,0,-1};

		int x, y; getHead(x,y);
		x += dx[opcode], y += dy[opcode];

		const int ERROR_CODE = -1;
		if (x<0 || x>=15)return ERROR_CODE;
		if (y<0 || y>=15)return ERROR_CODE;
		if (tile[x][y] >= 2)return ERROR_CODE;

		int score=0;
		if (tile[x][y] == -1)score = 500;
		else score = 0;

		int len=0;
		for (int r=0; r<15; r++){
			for (int c=0; c<15; c++){
				if (tile[r][c]>0) {
					len++;
					if (tile[x][y]!=-1)tile[r][c]--;
				}
			}
		}
		if (tile[x][y]==-1)len++;
		tile[x][y] = len;
		return score;
	}

public:
    friend std::ostream& operator <<(std::ostream &out, const board &b){
		out << "+------------------------------------------------------------------------+" << '\n';
		for (int r=0; r<15; r++){
			out << '|';
			for (int c=0; c<15; c++){
				out << ' ' << std::setw(3) << b.tile[r][c];
			}
			out << '|' << '\n';
		}
		out << "+------------------------------------------------------------------------+" << '\n';
		return out;
	}

private:
    std::array<std::array<int,15>,15> tile;
};
