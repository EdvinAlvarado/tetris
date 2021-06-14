#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include "include/SDL.h"
#include <Windows.h>
#endif
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <array>
#include <cmath>
#include <algorithm>
#include "tetris.hpp"
#include "IO.hpp"
#include "board.hpp"

using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;
using namespace std::chrono_literals;
// Will assume 4x4 tetromino until I can make the program work. Then I will expand code for iti
int main() {
	srand (time(NULL));	
	
	// Game Logic
	bool bGameOver = false;
	int nPosX = SCREEN_WIDTH / 2; // TODO get screen dimension accesible from here and const
	int nPosY = 0;
	int nTetromino = rand() % 7;
	
	Tetromino piece(nTetromino);
	Board board;
	IO io;
 	while (!bGameOver) {
		io.wait(50);
 		io.clearScreen(BLACK);
		io.sdlRect = io.makeRect(nPosX, nPosY, BLOCK_SIZE, BLOCK_SIZE);
		io.drawRect(RED);
		// Handle events queue
 		while (SDL_PollEvent(&io.sdlEvent) != 0) {
			// User requests quit
			if (io.sdlEvent.type == SDL_QUIT) {bGameOver = true;}
			else if (io.sdlEvent.type == SDL_KEYDOWN) {
				switch (io.sdlEvent.key.keysym.sym) {
					case SDLK_DOWN:
						nPosY++; 
						break;
					case SDLK_LEFT:
						nPosX--;
						break;
					case SDLK_RIGHT:
						nPosX++;
						break;
					case SDLK_z:
						piece.rotate();
						break;
				}
			}
		}
		io.updateScreen();
 	}

	// io.wait(1000);
	// TODO underfine reference in main.cpp?
	// std::this_thread::sleep_for(5000ms);
	cout << "Game Over!!" << endl;
	return 0;
}
