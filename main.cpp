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
#include "screen.hpp"
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
	int nPosX = BOARD_WIDTH / 2; // TODO get screen dimension accesible from here and const
	int nPosY = 0;
	int nTetromino = rand() % 7;
	
	Tetromino piece(nTetromino);
	Board board;
	IO io;
 	while (!bGameOver) {
		io.wait(50);
 		io.clearScreen(BLACK);
		// Handle events queue
 		while (SDL_PollEvent(&io.sdlEvent) != 0) {
			// User requests quit
			if (io.sdlEvent.type == SDL_QUIT) {bGameOver = true;}
			else if (io.sdlEvent.type == SDL_KEYDOWN) {
				boolBlocked bBlock = board.collisionChecker(nPosX, nPosY, piece);
				switch (io.sdlEvent.key.keysym.sym) {
					case SDLK_DOWN:
						if (!bBlock.down) {nPosY++;}
						break;
					case SDLK_LEFT:
						if (!bBlock.left) {nPosX--;}
						break;
					case SDLK_RIGHT:
						if (!bBlock.right) {nPosX++;}
						break;
					case SDLK_z:
						if (!bBlock.rotate) {piece.rotate();}
						break;
				}
			}
		}
		board.writeBoard(nPosX, nPosY, piece);
		io.printBoard(board);
		io.updateScreen();
 	}

	// TODO debugging only
	for (auto it = board.board.begin(); it < board.board.end(); it++) {
		for (auto itt = it->begin(); itt < it->end(); itt++) {
			std::cout << *itt << " ";
		}
		std::cout << std::endl;
	}
	// io.wait(1000);
	// std::this_thread::sleep_for(5000ms);
	cout << "Game Over!!" << endl;
	return 0;
}
