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
using std::sqrt;
using std::max;
using std::min;
using namespace std::chrono_literals;

#define VK_Z 0x5A // Windows Virtual-Key Z

struct tetromino {
	string s;
	size_t height;
	size_t width;
};

// Even 4x4 tetrominos only
// TODO handle any nxn size.
std::array<tetromino, 7> tetrominoList;
const int fieldWidth = 12;
const int fieldHeight = 18;
const int screenWidth = 30;
const int screenHeight = 70;
char fieldSymbolLegend[] = " ABCDEFG=#";

void rotateTetromino(tetromino& RotatedTetromino, const tetromino piece, int rotation) {
	switch (rotation % 4) {
		case 0:
			for (int i = 0; i < 16; i++) {RotatedTetromino.s[i] = piece.s[i];}
			RotatedTetromino.height = piece.height;
			RotatedTetromino.width = piece.width;
			break;
		case 1: // 90 degrees
			for (int i = 0; i < 16; i++) {RotatedTetromino.s[i] = piece.s[4 * (3 - i%4) + i/4];} 
			RotatedTetromino.height = piece.width;
			RotatedTetromino.width = piece.height;	
			break;
		case 2: // 180 degress
			for (int i = 0; i < 16; i++) {RotatedTetromino.s[i] = piece.s[15 - i];} 
			RotatedTetromino.height = piece.height;
			RotatedTetromino.width = piece.width;
			break;
		case 3: // 270 degrees
			for (int i = 0; i < 16; i++) {RotatedTetromino.s[i] = piece.s[3 - i/4 + 4 * (i%4)];}
			RotatedTetromino.height = piece.width;
			RotatedTetromino.width = piece.height;
			break;
	}
}

bool bDoesItFit(const tetromino starterPiece, int rotation, int nPosX, int nPosY, unsigned char action = VK_DOWN) {
	switch(action) {
		case VK_DOWN:
			return nPosY + starterPiece.height <= fieldHeight - 2;
			break;
		case VK_RIGHT:
			return nPosX + starterPiece.width - 1 < fieldWidth - 2;
			break;
		case VK_LEFT:
			return nPosX > 1;
			break;
		case VK_Z:
			return (nPosY + starterPiece.width <= fieldHeight - 2) && (nPosX + starterPiece.height < fieldWidth - 2) && (nPosX >= 1);
			break;
	}
	return false;	
}

size_t maxTetrominoWidth(const string sTetromino) {
	long long int m = 0;
	for (int tp = 0; tp < 4; tp++) {
		m = max(m, std::count(sTetromino.begin()+tp*4, sTetromino.begin()+4+tp*4, 'X'));
	}
	return m;
}

size_t maxTetrominoHeight(const string sTetromino) {
	size_t m = 4;
	for (int tp = 0; tp < 4; tp++) {
		if (std::count(sTetromino.begin()+tp*4, sTetromino.begin()+4+tp*4, 'X') == 0) {m--;}
	}
	return m;
}

// Will assume 4x4 tetromino until I can make the program work. Then I will expand code for iti
int main() {
	srand (time(NULL));	
	
	// To assure accurate collission physics and to simplify application all tetromino Xs should be in the top left.	
	// TODO Alternative would be basically retooling the program to accept variable shape tetrominos.
	tetrominoList[0].s.append("X...");
	tetrominoList[0].s.append("X...");
	tetrominoList[0].s.append("X...");
	tetrominoList[0].s.append("X...");
	tetrominoList[0].height = maxTetrominoHeight(tetrominoList[0].s);
	tetrominoList[0].width = maxTetrominoWidth(tetrominoList[0].s);

	tetrominoList[1].s.append("XX..");
	tetrominoList[1].s.append("XX..");
	tetrominoList[1].s.append("....");
	tetrominoList[1].s.append("....");
	tetrominoList[1].height = maxTetrominoHeight(tetrominoList[1].s);
	tetrominoList[1].width = maxTetrominoWidth(tetrominoList[1].s);

	tetrominoList[2].s.append(".X..");
	tetrominoList[2].s.append("XX..");
	tetrominoList[2].s.append("X...");
	tetrominoList[2].s.append("....");
	tetrominoList[2].height = maxTetrominoHeight(tetrominoList[2].s);
	tetrominoList[2].width = maxTetrominoWidth(tetrominoList[2].s);

	tetrominoList[3].s.append("X...");
	tetrominoList[3].s.append("XX..");
	tetrominoList[3].s.append(".X..");
	tetrominoList[3].s.append("....");
	tetrominoList[3].height = maxTetrominoHeight(tetrominoList[3].s);
	tetrominoList[3].width = maxTetrominoWidth(tetrominoList[3].s);

	tetrominoList[4].s.append("XX..");
	tetrominoList[4].s.append("X...");
	tetrominoList[4].s.append("X...");
	tetrominoList[4].s.append("....");
	tetrominoList[4].height = maxTetrominoHeight(tetrominoList[4].s);
	tetrominoList[4].width = maxTetrominoWidth(tetrominoList[4].s);

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
	// int nSpeedCount = 0;
	// bool bForceDown = false;
	// int nSpeed = 20;
	bool bKey[4];
	unsigned char vkInputKeys[4] = {VK_RIGHT, VK_LEFT, VK_DOWN, VK_Z};	
	int nCurrentX = fieldWidth / 2;
	int nCurrentY = 0;
	int nRotation = 0;
	int nTetromino = (rand() + 1) % tetrominoList.size();
	tetromino piece = tetrominoList[nTetromino];

	while (!bGameOver) {

		// Timing
		std::this_thread::sleep_for(200ms);
		// nSpeedCount++;
		// bForceDown = (nSpeedCount == nSpeed);

		// Input
		// GetAsyncKeyState returns a short with the most significant bit set i.e. 0x8000
		for (int k = 0; k < 4; k++) {bKey[k] = (0x8000 & GetAsyncKeyState(vkInputKeys[k]));}
		if (bKey[0] == true && bDoesItFit(tetrominoList[nTetromino], nRotation, nCurrentX, nCurrentY, vkInputKeys[0])) {nCurrentX++;}
		if (bKey[1] == true && bDoesItFit(tetrominoList[nTetromino], nRotation, nCurrentX, nCurrentY, vkInputKeys[1])) {nCurrentX--;}
		if (bKey[2] == true && bDoesItFit(tetrominoList[nTetromino], nRotation, nCurrentX, nCurrentY, vkInputKeys[2])) {nCurrentY++;} 
		if (bKey[3] == true && bDoesItFit(tetrominoList[nTetromino], nRotation, nCurrentX, nCurrentY, vkInputKeys[3])) {rotateTetromino(piece, tetrominoList[nTetromino], ++nRotation);}
		
		// for (int i = 0; i < 16; i++) {screen[screenWidth + i] = piece.s[i] == 'X' ? fieldSymbolLegend[nTetromino + 1] : ' ';}
		
		// Redraw field
		// FIXME: would delete the lines that are left in the end.
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				field[y][x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 9 : 0;
			}
		}

		// Tetromino
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				field[y + nCurrentY][x + nCurrentX] = piece.s[y * 4 + x] == 'X' ? nTetromino + 1 : field[y + nCurrentY][x + nCurrentX];
			}
		}
	
		// Draw Field offset to (2,2)
		for (int y = 0; y < fieldHeight; y++) {
			for (int x = 0; x < fieldWidth; x++) {
				screen[(y+2)*screenWidth + (x+2)] = fieldSymbolLegend[field[y][x]];
			}
		}

		// FIXME not spinning
		screen[0] = nCurrentX + '0';
		screen[1] = nCurrentY + '0';
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
