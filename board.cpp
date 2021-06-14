#include "board.hpp"
#include <iostream>
#include <numeric>
#include "tetris.hpp"
#include <algorithm>

bool Board::checkLineFilled(int line) {
	if (line < BOARD_HEIGHT) {
		return (std::accumulate(board[line].begin(), board[line].end(), 0, [](int pos){return pos > 0? 1:0;}) == BOARD_WIDTH) // assumes only POS_FREE and POS_FILLED
	} else {std::cerr << "Out of bound line" << std::endl;}
}

void Board::writeBoard(int pX, int pY, Tetromino piece) {
	board = backBoard;
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.retro[y][x] > 0) {board[y+pY][x+pX] = piece.type;}
		}
	}
}
