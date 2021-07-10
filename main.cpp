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
	srand (time(0));	
	
	// Game Logic
	bool bGameOver = false;
	int nPosX = BOARD_WIDTH / 2; 
	int nPosY = 0;

	Tetromino piece(rand() % 7);
	Board board;
	IO io;

	Uint32 loopStartTime = SDL_GetTicks();
 	while (!bGameOver) {
		boolBlocked bBlock = board.collisionChecker(nPosX, nPosY, piece);
		// Handle events queue
 		while (SDL_PollEvent(&io.sdlEvent) != 0) {
			// User requests quit
			if (io.sdlEvent.type == SDL_QUIT) {bGameOver = true;}
			// Handles all key presses
			else if (io.sdlEvent.type == SDL_KEYDOWN) {
				switch (io.sdlEvent.key.keysym.sym) {
					case SDLK_DOWN:
						if (!bBlock.down) {
							nPosY++;
							// Provides smooth(ish) tetris movements
							// FIXME keeps going down for a while after letting the key go
	 						while (SDL_PollEvent(&io.sdlEvent) != 0) {
								if (io.sdlEvent.key.keysym.sym == SDLK_DOWN && !bBlock.down) {
									nPosY++;
									board.writeBoard(nPosX, nPosY, piece);
									io.updateScreen(BLACK, board);
									bBlock = board.collisionChecker(nPosX, nPosY, piece);
									io.wait(50);		
								}
								else {io.clearEvent();}
							}					
						}
						break;
					case SDLK_LEFT:
						if (!bBlock.left) {
							nPosX--;
							// Provides smooth(ish) tetris movements
 							while (SDL_PollEvent(&io.sdlEvent) != 0) {
								if (io.sdlEvent.key.keysym.sym == SDLK_LEFT && !bBlock.left) {
									nPosX--;
									board.writeBoard(nPosX, nPosY, piece);
									io.updateScreen(BLACK, board);
									bBlock = board.collisionChecker(nPosX, nPosY, piece);
									io.wait(50);		
								}
								else {io.clearEvent();}
							}
						}
						break;
					case SDLK_RIGHT:
						if (!bBlock.right) {
							nPosX++;
							// Provides smooth(ish) tetris movements
							while (SDL_PollEvent(&io.sdlEvent) != 0) {
								if (io.sdlEvent.key.keysym.sym == SDLK_RIGHT && !bBlock.right) {
									nPosX++;
									board.writeBoard(nPosX, nPosY, piece);
									io.updateScreen(BLACK, board);
									bBlock = board.collisionChecker(nPosX, nPosY, piece);
									io.wait(50);		
								}
								else {io.clearEvent();}
							}					
						}
						break;
					case SDLK_z:
						if (!bBlock.rotate) {piece.rotate();}
						break;
				}
				io.clearEvent();
			}
		}
		
		
		if (io.elapsedTime(loopStartTime) > 500) {
			loopStartTime = SDL_GetTicks();
			if (!bBlock.down) {nPosY++;}
			else {
				board.writeBackBoard(nPosX, nPosY, piece);
				board.filledLineCleaner(); // Needs to be under writeBackBoard so it cleans the piece
				nPosX = BOARD_WIDTH / 2; 
				nPosY = 0;
				piece = Tetromino(rand() % 7);
			}	
		}
		io.wait(50);
		board.writeBoard(nPosX, nPosY, piece);
		io.updateScreen(BLACK, board);
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
	cout << "Game Over!!" << " score: " << board.score <<  endl;
	return 0;
}
