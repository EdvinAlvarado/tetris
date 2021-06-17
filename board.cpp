#include "board.hpp"
#include <iostream>
#include <numeric>
#include "tetris.hpp"
#include <algorithm>

bool Board::checkLineFilled(int line) {
	if (line < BOARD_HEIGHT) {
		return std::find(board[line].begin(), board[line].end(), 0) == board[line].end();
	} else {std::cerr << "Out of bound line" << std::endl;}
}

void Board::writeBoard(int pX, int pY, Tetromino piece) {
	board = backBoard;
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.tetro[y][x] > 0) {board[y+pY][x+pX] = piece.type;}
		}
	}
}
