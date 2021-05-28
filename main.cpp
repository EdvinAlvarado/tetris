#include <Windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <array>
#include <cmath>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;
using namespace std::chrono_literals;

#define VK_Z 0x5A // Windows Virtual-Key Z
//---------------------------------------------------------------------------------------------------------
class Tetromino {
	public:
		string s;
		size_t height;
		size_t width;
		void rotate();
		Tetromino(string tetromino) {
			height = maxTetrominoHeight(tetromino);
			width = maxTetrominoWidth(tetromino);
			s = trimTetromino(tetromino);
		}
	private:
		size_t maxTetrominoWidth(string sTetromino);
		size_t maxTetrominoHeight(string sTetromino);
		string trimTetromino(string sTetromino);
};

void Tetromino::rotate() {
	string sRotatedTetromino;
	for (size_t i = 0; i < width*height-1; i++) {
		sRotatedTetromino[(height-1)*width - width*(i%height) + (i/height)] = s[i];
	}
	s = sRotatedTetromino;
	std::swap(height, width);
}

// Assumes sTetromino is NxN
// std::count brings a ptrdiff_t which is basically a long int. std::max can't handle the simple task of matching an int with ptrdiff_t so m needs to be ptrdiff_t.
size_t Tetromino::maxTetrominoWidth(string sTetromino) {
	size_t m = 0;
	size_t nTetrominoSize = std::sqrt(sTetromino.length());
	for (size_t tp = 0; tp < nTetrominoSize; tp++) {
		string sRow = sTetromino.substr(tp * nTetrominoSize, tp*nTetrominoSize+ nTetrominoSize);
		m = std::max(m, sRow.find_last_of('X') - sRow.find_first_of('X') + 1);
	}
	return m;
}

// Assumes sTetromino is NxN
size_t Tetromino::maxTetrominoHeight(string sTetromino) {
	size_t m = 4;
	size_t nTetrominoSize = std::sqrt(sTetromino.length());
	for (size_t tp = 0; tp < nTetrominoSize; tp++) {
		string sRow = sTetromino.substr(tp * nTetrominoSize, tp*nTetrominoSize+ nTetrominoSize);
		if (std::count(sRow.begin(), sRow.end(), 'X') == 0) {m--;}
	}
	return m;
}

// Must be called after maxTetrominoHeight and maxTetrominoWidth
string Tetromino::trimTetromino(string sTetromino) {
	string sTrimmedTetromino;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			sTrimmedTetromino[y*width + x] = sTetromino[y*width + x];
		}
	}
	return sTrimmedTetromino;
}
// ----------------------------------------------------------------------------------------------------------------------
// Even 4x4 tetrominos only
// TODO handle any nxn size.
std::array<string, 7> tetrominoList;
const int fieldWidth = 12;
const int fieldHeight = 18;
const int screenWidth = 30;
const int screenHeight = 70;
char fieldSymbolLegend[] = " ABCDEFG=#";

bool bDoesItFit(Tetromino tetromino, int nPosX, int nPosY, unsigned char action = VK_DOWN) {
	switch(action) {
		case VK_DOWN:
			return nPosY + tetromino.height <= fieldHeight - 2;
			break;
		case VK_RIGHT:
			return nPosX + tetromino.width - 1 < fieldWidth - 2;
			break;
		case VK_LEFT:
			return nPosX > 1;
			break;
		case VK_Z:
			return (nPosY + tetromino.width <= fieldHeight - 2) && (nPosX + tetromino.height < fieldWidth - 2) && (nPosX >= 1);
			break;
	}
	return false;	
}

// Will assume 4x4 tetromino until I can make the program work. Then I will expand code for iti
int main() {
	srand (time(NULL));	
	
	// To assure accurate collission physics and to simplify application all tetromino Xs should be in the top left.	
	// TODO Alternative would be basically retooling the program to accept variable shape tetrominos.
	tetrominoList[0].append("X...");
	tetrominoList[0].append("X...");
	tetrominoList[0].append("X...");
	tetrominoList[0].append("X...");

	tetrominoList[1].append("XX..");
	tetrominoList[1].append("XX..");
	tetrominoList[1].append("....");
	tetrominoList[1].append("....");

	tetrominoList[2].append(".X..");
	tetrominoList[2].append("XX..");
	tetrominoList[2].append("X...");
	tetrominoList[2].append("....");

	tetrominoList[3].append("X...");
	tetrominoList[3].append("XX..");
	tetrominoList[3].append(".X..");
	tetrominoList[3].append("....");

	tetrominoList[4].append("XX..");
	tetrominoList[4].append("X...");
	tetrominoList[4].append("X...");
	tetrominoList[4].append("....");

	tetrominoList[5].append("XX..");
	tetrominoList[5].append(".X..");
	tetrominoList[5].append(".X..");
	tetrominoList[5].append("....");

	tetrominoList[6].append("XXX.");
	tetrominoList[6].append(".X..");
	tetrominoList[6].append("....");
	tetrominoList[6].append("....");

	// Field Boundary
	int field[fieldHeight][fieldWidth];
	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHeight; y++) {
			field[y][x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 9 : 0;
		}
	}

	// Create Screen Buffer
	// screen needs to be onedimensional to use WriteConsoleOutputCharacter(...)
	char screen[screenWidth*screenHeight]; 
	for (int i = 0; i < screenHeight*screenWidth; i++) {screen[i] = ' ';}
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Game Logic
	bool bGameOver = false;
	bool bNextPiece = false;
	bool bKey[4];
	unsigned char vkInputKeys[4] = {VK_RIGHT, VK_LEFT, VK_DOWN, VK_Z};	
	int nCurrentX = fieldWidth / 2;
	int nCurrentY = 0;
	int nTetromino = (rand() + 1) % tetrominoList.size();
	Tetromino piece(tetrominoList[nTetromino]);

	while (!bGameOver) {

		// Timing
		std::this_thread::sleep_for(200ms);

		// Cleaning Game Logic for next piece
		if (bNextPiece) {
			nCurrentX = fieldWidth / 2;
			nCurrentY = 0;
			nTetromino = (rand() + 1) % tetrominoList.size();
			bNextPiece = false;
		}

		// Input
		// GetAsyncKeyState returns a short with the most significant bit set i.e. 0x8000
		for (int k = 0; k < 4; k++) {bKey[k] = (0x8000 & GetAsyncKeyState(vkInputKeys[k]));}
		if (bKey[0] == true && bDoesItFit(piece, nCurrentX, nCurrentY, vkInputKeys[0])) {nCurrentX++;}
		if (bKey[1] == true && bDoesItFit(piece, nCurrentX, nCurrentY, vkInputKeys[1])) {nCurrentX--;}
		if (bKey[2] == true && bDoesItFit(piece, nCurrentX, nCurrentY, vkInputKeys[2])) {nCurrentY++;} 
		if (bKey[3] == true && bDoesItFit(piece, nCurrentX, nCurrentY, vkInputKeys[3])) {piece.rotate();}
		
		// Redraw field
		// FIXME: would delete the lines that are left in the end.
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				field[y][x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 9 : 0;
			}
		}

		// Tetromino
		for (size_t y = 0; y < piece.height; y++) {
			for (size_t x = 0; x < piece.width; x++) {
				field[y + nCurrentY][x + nCurrentX] = piece.s[y*piece.width + x] == 'X' ? nTetromino + 1 : field[y + nCurrentY][x + nCurrentX];
			}
		}
	
		// Draw Field offset to (2,2)
		for (int y = 0; y < fieldHeight; y++) {
			for (int x = 0; x < fieldWidth; x++) {
				screen[(y+2)*screenWidth + (x+2)] = fieldSymbolLegend[field[y][x]];
			}
		}

		int i = fieldWidth;
		for (size_t y = 0; y < piece.height; y++) {
			for (size_t x = 0; x < piece.width; x++) {
				screen[i++] = piece.s[y*piece.width + x];
			}
		}
		screen[0] = piece.width + '0';
		screen[1] = piece.height + '0';
		screen[3] = nCurrentX + '0';
		screen[4] = nCurrentY + '0';
		// screen[0] = bKey[0] == true && bDoesItFit(piece, nCurrentX, nCurrentY, vkInputKeys[0]) ? 'R' : ' ';
		// screen[1] = bKey[1] == true && bDoesItFit(tetrominoList[nTetromino], nRotation, nCurrentX, nCurrentY, vkInputKeys[1]) ? 'L' : ' ';
		// screen[2] = bKey[2] == true && bDoesItFit(tetrominoList[nTetromino], nRotation, nCurrentX, nCurrentY, vkInputKeys[2]) ? 'D' : ' ';
		// screen[3] = bKey[3] == true && bDoesItFit(tetrominoList[nTetromino], nRotation, nCurrentX, nCurrentY, vkInputKeys[3]) ? 'Z' : ' ';
	
		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &dwBytesWritten);
	}
	CloseHandle(hConsole);
	cout << "Game Over!!" << endl;
	system("pause");
	return 0;
}
