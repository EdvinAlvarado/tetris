#ifndef _BOARD_
#define _BOARD_

#include <array>
#include "tetris.hpp"
#include "screen.hpp"
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
		bool checkLineFilled(int line);
		void rollLines(int delLine); // deletes the content of line and rolls all the lines on top down.
		bool checkPosInBound(int pX, int pY);
	public:
		void writeBoard(int pX, int pY, Tetromino piece);
		void writeBackBoard(int pX, int pY, Tetromino piece);
		std::array<std::array<int,BOARD_WIDTH>,BOARD_HEIGHT> board; // contains the pieces.
		boolBlocked collisionChecker(int pX, int pY, Tetromino piece);
		unsigned int filledLineCleaner();
};
#endif
