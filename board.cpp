#include "board.hpp"
#include <iostream>
#include <numeric>
#include "tetris.hpp"
#include <algorithm>

bool Board::checkLineFilled(int line) {
	if (line < BOARD_HEIGHT || line >= 0) {
		return std::find(board[line].begin(), board[line].end(), 0) == board[line].end();
	} else {std::cerr << "Out of bound line" << std::endl;}
	return false;
}

void Board::writeBoard(int pX, int pY, Tetromino piece) {
	board = backBoard;
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.tetro[y][x] > 0) {board[y+pY][x+pX] = piece.type;}
		}
	}
}

void Board::writeBackBoard(int pX, int pY, Tetromino piece) {
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.tetro[y][x] > 0) {backBoard[y+pY][x+pX] = piece.type;}
		}
	}
}

boolBlocked Board::collisionChecker(int pX, int pY, Tetromino piece) {
	Tetromino pi = piece;
	boolBlocked bDir;
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.tetro[y][x] > 0) {
				if (x+pX <= 0) {bDir.left = true;}
				else if (backBoard[y+pY][x+pX-1] > 0) {bDir.left = true;}
				if (x+pX >= BOARD_WIDTH-1) {bDir.right = true;}
				else if (backBoard[y+pY][x+pX+1] > 0) {bDir.right = true;}
				if (y+pY >= BOARD_HEIGHT-1) {bDir.down = true;}
				else if (backBoard[y+pY+1][x+pX] > 0) {bDir.down = true;}
			}
		}
	}
	for (int r = 0; r < 3; r++) {// 4 rotations
		pi.rotate();
		for (int y = 0; y < PIECE_SIZE; y++) {
			for (int x = 0; x < PIECE_SIZE; x++) {
				if (pi.tetro[y][x] > 0) {
					// left || right || down || overlap
					if (x+pX <= 0 || x+pX >= BOARD_WIDTH-1 || y+pY >= BOARD_HEIGHT-1 || backBoard[y+pY][x+pX] > 0) {bDir.rotate = true;}
				}
			}
		}
	}
	return bDir;
}

void Board::rollLines(int delLine) {
	for (int line = 0; line < delLine; line++) {
		switch(line) {
			case 0:
				std::fill(backBoard[line].begin(), backBoard[line].end(), 0); break;
			default:
				backBoard[line+1] = backBoard[line];
		}
	}
}

unsigned int Board::filledLineCleaner() {
	unsigned int sc = 0;
	for (int line = 0; line < BOARD_HEIGHT; line++) {
		if (checkLineFilled(line)) {
			sc++;
			rollLines(line);
		}
	}
	return sc;
}
