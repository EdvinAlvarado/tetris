#ifndef _BOARD_
#define _BOARD_

#include <array>
#include "tetris.hpp"
#include "screen.hpp"
#define BLOCK_SIZE 10 // Width and Height of each block of a piece
#define BOARD_WIDTH SCREEN_WIDTH/BLOCK_SIZE // Board width in blocks
#define BOARD_HEIGHT SCREEN_HEIGHT/BLOCK_SIZE // Board height in blocks

// TODO consider eliminating
enum position {POS_FREE, POS_FILLED}; // POS_FREE = free position of the board; POS_FILLED = filled position of the board

struct boolBlocked {
	bool down;
	bool left;
	bool right;
	bool rotate;
};

class Board {
	private:
		std::array<std::array<int,BOARD_WIDTH>,BOARD_HEIGHT> backBoard; // contains the pieces.
	public:
		void writeBoard(int pX, int pY, Tetromino piece);
		void writeBackBoard(int pX, int pY, Tetromino piece);
		bool checkLineFilled(int line);
		std::array<std::array<int,BOARD_WIDTH>,BOARD_HEIGHT> board; // contains the pieces.
		boolBlocked collisionChecker(int pX, int pY, Tetromino piece);
};
#endif
