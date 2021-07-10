#include "IO.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "board.hpp"
#include "screen.hpp"


// TODO Consider adding int returns for error handling.
// Initialize SDL Graphics
int IO::initGraph() {
	// Initialize the SDL video system and reports any error.
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		std::cerr << "Couldn't initialize SDL" << SDL_GetError() << std::endl;
		return INIT_ERROR;
	}
	atexit(SDL_Quit); // activates the function to clean initialized system when program exits normally.

	sdlWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (sdlWindow == NULL) {
		std::cerr << "Window could not be created" << SDL_GetError() << std::endl;
		return WINDOW_ERROR;
	}

	sdlScreen = SDL_GetWindowSurface(sdlWindow);
	return INIT_PASS;
}

// Initialization
IO::IO() {
	initGraph();
	initColors();
}

// Clear the screen to black
void IO::clearScreen(enum color pColor) {
	if (SDL_FillRect(sdlScreen, NULL, rgbColors[pColor]) < 0){
		std::cerr << "Filling screen of a color failed: " << SDL_GetError() << std::endl;
	};
}

// Draws a rectangle of any color.
// TODO make it print a piece.
//  void IO::drawScreen(int pX1, int pY1, int pX2, int pY2, enum color pColor) {
// 
//  }

// Return screen height
int IO::getScreenHeight() {
	return sdlScreen->h;
}

// Return screen width
int IO::getScreenWidth() {
	return sdlScreen->w;
}

// Update screen
void IO::updateScreen(enum color pColor, Board gameBoard) {
	clearScreen(pColor);
	displayScreenOverlay();
	printBoard(gameBoard);
	SDL_UpdateWindowSurface(sdlWindow);
}

// Make SDL wait milliseconds
void IO::wait(int mseconds) {
	SDL_Delay(mseconds);
}

void IO::initColors() {
	for (int pColor = 0; pColor < COLOR_MAX; pColor++) {
		switch(pColor) {
			case BLACK:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0x00, 0x00, 0x00); break;
			case RED:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0xFF, 0x00, 0x00); break;
			case GREEN:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0x00, 0xFF, 0x00); break;
			case BLUE:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0x00, 0x00, 0xFF); break;
			case CYAN:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0x00, 0xFF, 0xFF); break;
			case MAGENTA:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0xFF, 0x00, 0xFF); break;
			case YELLOW:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0xFF, 0xFF, 0x00); break;
			case WHITE:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0xFF, 0xFF, 0xFF); break;
			case GREY:
				rgbColors[pColor] = SDL_MapRGB(sdlScreen->format, 0x80, 0x80, 0x80); break;
		}
	}
}

SDL_Rect IO::makeRect(int posX, int posY, int width, int height) {
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = width;
	rect.h = height;
	return rect;
}

// Draws a rectangle of any color.
void IO::drawRect(enum color pColor) {
	if (SDL_FillRect(sdlScreen, &sdlRect, rgbColors[pColor]) < 0){
		std::cerr << "Filling rectangle of a color failed: " << SDL_GetError() << std::endl;
	};
 }

// SCREEN_WIDTH and SCREEN_HEIGHT must be equal or greater than BOARD_WIDTH and BOARD_HEIGHT
void IO::printBoard(Board gameBoard) {
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			sdlRect = makeRect(x*BLOCK_SIZE + x_offset, y*BLOCK_SIZE + y_offset, BLOCK_SIZE, BLOCK_SIZE);
			drawRect(static_cast<color>(gameBoard.board[y][x]));
		}
	}
}

// SDL_PollEvent checks the events in queue and pops them out. Repeate function and sdlEvent will be empty.
void IO::clearEvent() {
	while (SDL_PollEvent(&sdlEvent) != 0) {continue;} 
}

// SDL_GetTicks gives you milliseconds since SDL libary started
unsigned int IO::elapsedTime(Uint32 startTime) {
	Uint32 currTime = SDL_GetTicks();
	return static_cast<unsigned int>(currTime - startTime);
}

void IO::displayScreenOverlay() {
	if (x_offset > 0) {
		sdlRect = makeRect(x_offset - BLOCK_SIZE, 0, BLOCK_SIZE, SCREEN_HEIGHT);
		drawRect(GREY);
		sdlRect = makeRect(x_offset + BOARD_WIDTH* BLOCK_SIZE, 0, BLOCK_SIZE, SCREEN_HEIGHT);
		drawRect(GREY);
	}
}
