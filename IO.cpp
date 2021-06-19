#include "IO.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "board.hpp"


// TODO Consider adding int returns for error handling.
// Initialize SDL Graphics
int IO::initGraph() {
	// Initialize the SDL video system and reports any error.
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		std::cerr << "Couldn't initialize SDL" << SDL_GetError() << std::endl;
		return INIT_ERROR;
	}
	atexit(SDL_Quit); // activates the function to clean initialized system when program exits normally.

	// Set 640 x 480 video mode
	sdlWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (sdlWindow == NULL) {
		std::cerr << "Window could not be created" << SDL_GetError() << std::endl;
		return WINDOW_ERROR;
	}

	sdlScreen = SDL_GetWindowSurface(sdlWindow);
	initColors();
	return INIT_PASS;
}

// Initialization
// TODO move initcolors over here
IO::IO() {
	initGraph();
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
void IO::updateScreen() {
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
// TODO erase after testing
void IO::drawRect(enum color pColor) {
	if (SDL_FillRect(sdlScreen, &sdlRect, rgbColors[pColor]) < 0){
		std::cerr << "Filling rectangle of a color failed: " << SDL_GetError() << std::endl;
	};
 }

void IO::printBoard(Board gameBoard) {
	for (int y = 0; y < SCREEN_HEIGHT; y+=BLOCK_SIZE) {
		for (int x = 0; x < SCREEN_WIDTH; x+=BLOCK_SIZE) {
			sdlRect = makeRect(x, y, BLOCK_SIZE, BLOCK_SIZE);
			drawRect(static_cast<color>(gameBoard.board[y/BLOCK_SIZE][x/BLOCK_SIZE]));
		}
	}
}
