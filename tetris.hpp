#ifndef _TETRIS_
#define _TETRIS_

#include <array>

#define PIECE_SIZE 5

class Tetromino {
	
	public:
		void rotate();
		std::array<std::array<int,PIECE_SIZE>,PIECE_SIZE> tetro;
		Tetromino(int piece_number);
		int type;
};


#endif
