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
// using namespace std::this_thread;

// Even tetrominos only
std::array<string, 7> tetromino;
const int fieldWidth = 12;
const int fieldHeight = 18;
const int screenWidth = 30;
const int screenHeight = 70;
// unsigned char* field = nullptr;
char fieldSymbolLegend[] = " ABCDEFG=#";

string sRotate(string const& sTetromino, int nRotation) {
	
	string sRotatedTetromino;
	size_t n = sqrt(sTetromino.length());
	switch (nRotation % 4) {
		case 0:
			return sTetromino; break;
		case 1: // 90 degrees
			for (int i = 0; i < sTetromino.length(); i++) {sRotatedTetromino[i] = sTetromino[n-1 - (i/n) + n * i%n];} break;
		case 2: // 180 degress
			for (int i = 0; i < sTetromino.length(); i++) {sRotatedTetromino[i] = sTetromino[n*n-1 - i];} break;
		case 3: // 270 degrees
			for (int i = 0; i < sTetromino.length(); i++) {sRotatedTetromino[i] = sTetromino[n * (n-1 - i%n) + i/n];} break;
	}
	return sRotatedTetromino;
}
int main() {	
	
	tetromino[0].append("..X.");
	tetromino[0].append("..X.");
	tetromino[0].append("..X.");
	tetromino[0].append("..X.");

	tetromino[1].append("....");
	tetromino[1].append(".XX.");
	tetromino[1].append(".XX.");
	tetromino[1].append("....");

	tetromino[2].append("..X.");
	tetromino[2].append(".XX.");
	tetromino[2].append(".X..");
	tetromino[2].append("....");

	tetromino[3].append(".X..");
	tetromino[3].append(".XX.");
	tetromino[3].append("..X.");
	tetromino[3].append("....");

	tetromino[4].append(".XX.");
	tetromino[4].append(".X..");
	tetromino[4].append(".X..");
	tetromino[4].append("....");

	// Field Boundary
	char field[fieldHeight][fieldWidth];
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
	int nSpeedCount = 0;
	bool bForceDown = false;
	int nSpeed = 20;
	bool bKey[4];
	unsigned char vkInputKeys[4] = {VK_RIGHT, VK_LEFT, VK_DOWN, 0x5A}; // Windows Virtual-Key Codes. 0x5A = Z key
	int nCurrentRotation = 0;
	int nCurrentX = fieldWidth / 2;
	int nCurrentY = 0;
	int nTetromino = (rand() + 1) % tetromino.size();
	int nRotation = 0;

	while (!bGameOver) {

		// Timing
		std::this_thread::sleep_for(50ms);
		nSpeedCount++;
		bForceDown = (nSpeedCount == nSpeed);

		// Input
		// GetAsyncKeyState returns a short with the most significant bit set i.e. 0x80
		for (int k = 0; k < 4; k++) {
			bKey[k] = (0x80 & GetAsyncKeyState(vkInputKeys[k])) == 0xFF;
		}
		if (bKey[0] == true) {nCurrentX = min(nCurrentX + 1, fieldWidth - 2);}
		if (bKey[1] == true) {nCurrentX = max(nCurrentX - 1, 1);}
		if (bKey[2] == true) {nCurrentY = max(nCurrentY - 1, 1);} // TODO need to consider higher floor.
		if (bKey[3] == true) {nRotation = (nRotation + 1) % 4;}

		// Tetromino
		for (int y = 0; y < sqrt(tetromino[nTetromino].length()); y++) {
			for (int x = 0; x < sqrt(tetromino[nTetromino].length()); x++) {
				field[y][x] = sRotate(tetromino[nTetromino], nRotation)[y * sqrt(tetromino[nTetromino].length()) + x] == 'X' ? fieldSymbolLegend[nTetromino] : 0;
			}
		}
	
		// Draw Field offset to (2,2)
		for (int y = 0; y < fieldHeight; y++) {
			for (int x = 0; x < fieldWidth; x++) {
				screen[(y+2)*screenWidth + (x+2)] = fieldSymbolLegend[field[y][x]];
			}
		}

		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, {0, 0}, &dwBytesWritten);
	}


	CloseHandle(hConsole);
	cout << "Game Over!!" << endl;
	system("pause");
	return 0;
}