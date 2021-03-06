#include "board.hpp"
#include <array>
#include <iostream>
#include <numeric>
#include "tetris.hpp"
#include <algorithm>
#include <utility>

Board::Board() {
	score = 0;
}

bool Board::checkPosInBound(int pX, int pY) {
	if (pY < BOARD_HEIGHT || pX < BOARD_WIDTH || pX >= 0 || pY >= 0) {return true;}
	else {
		return false;
		std::cerr << "Out of bound position: (" << pX << "," << pY << ")" << std::endl;
	}
}

bool Board::checkLineFilled(int line) {
	if (line < BOARD_HEIGHT || line >= 0) {
		return std::find(board[line].begin(), board[line].end(), 0) == board[line].end();
	} else {std::cerr << "Out of bound line" << std::endl;}
	return false;
}

void Board::writeBoard(int pX, int pY, Tetromino piece) {
	board = backBoard;
	int delta_y = fallPosY(pX, pY, piece);
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.tetro[y][x] > 0) {
				if (checkPosInBound(x+pX, y+pY)) {
					board[y+pY][x+pX] = piece.type;
					board[y+pY+delta_y][x+pX] = -piece.type;
				} 
			}
		}
	}
}

void Board::writeBackBoard(int pX, int pY, Tetromino piece) {
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.tetro[y][x] > 0) {
				if (checkPosInBound(x+pX, y+pY)) {backBoard[y+pY][x+pX] = piece.type;}
			}
		}
	}
}

boolBlocked Board::collisionChecker(int pX, int pY, Tetromino piece) {
	Tetromino pi = piece;
	pi.rotate();
	boolBlocked bDir;

	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			if (piece.tetro[y][x] > 0) {
				checkPosInBound(x+pX, y+pY);
				if (x+pX <= 0) {bDir.left = true;}
				else if (backBoard[y+pY][x+pX-1] > 0) {bDir.left = true;}
				if (x+pX >= BOARD_WIDTH-1) {bDir.right = true;}
				else if (backBoard[y+pY][x+pX+1] > 0) {bDir.right = true;}
				if (y+pY >= BOARD_HEIGHT-1) {bDir.down = true;}
				else if (backBoard[y+pY+1][x+pX] > 0) {bDir.down = true;}
			}
			if (pi.tetro[y][x] > 0) {
				// left || right || down || overlap
				if (x+pX < 0 || x+pX >= BOARD_WIDTH || y+pY >= BOARD_HEIGHT-1 || backBoard[y+pY][x+pX] > 0) {bDir.rotate = true;}

			}
		}
	}
	return bDir;
}

void Board::rollLines(int delLine) {
	if (delLine >= BOARD_HEIGHT || delLine < 0) {
		std::cerr << "Out of bound line" << std::endl;
	} else {
		for (int line = delLine; line >= 0; line--) {
			switch(line) {
				case 0:
					std::fill(backBoard[line].begin(), backBoard[line].end(), 0); break;
				default:
					backBoard[line] = backBoard[line-1];
			}
		}
	}
}

// Provides score
void Board::filledLineCleaner() {
	for (int line = 0; line < BOARD_HEIGHT; line++) {
		if (checkLineFilled(line)) {
			score++;
			rollLines(line);
		}
	}
}

// Provides the lowest y position they can go.
int Board::fallPosY(int pX, int pY, Tetromino piece) {
	int y = 0;
	while (!collisionChecker(pX, pY+y, piece).down) {
		y++;
	}
	return y;
}
