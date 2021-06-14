#ifndef _BOARD_
#define _BOARD_

#include "IO.hpp"
#include <array>
#include "tetris.hpp"

#define BLOCK_SIZE 10 // Width and Height of each block of a piece
#define BOARD_WIDTH SCREEN_WIDTH/BLOCK_SIZE // Board width in blocks
#define BOARD_HEIGHT SCREEN_HEIGHT/BLOCK_SIZE // Board height in blocks
#define VERTICAL_MARGIN 20 // Minimum vertical margin for the board limit
#define HORIZONTAL_MARGIN 20 // Minimum horizontal margin for the board limit

enum {POS_FREE, POS_FILLED} // POS_FREE = free position of the board; POS_FILLED = filled position of the board

class Board {
	private:
		std::array<std::array<int,BOARD_WIDTH>,BOARD_HEIGHT> backBoard; // contains the pieces.
	public:
		void writeBoard(int pX, int pY, Tetromino piece);
		bool checkLineFilled(int line);
		std::array<std::array<int,BOARD_WIDTH>,BOARD_HEIGHT> board; // contains the pieces.
};
#endif
