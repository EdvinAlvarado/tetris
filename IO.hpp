#ifndef _IO_
#define _IO_

#include <SDL2/SDL.h>
#include "screen.hpp"
#include "board.hpp"


// one color for each tetromino plus black
// colors 1 thru 7 will be the tetromino colors.
enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, GREY, COLOR_MAX}; 
enum initErrors {INIT_PASS, INIT_ERROR, WINDOW_ERROR};

class IO {
	private:
		SDL_Window* sdlWindow;
		SDL_Surface* sdlScreen;
		Uint32 rgbColors[COLOR_MAX];
		int initGraph();
		void initColors();
		void printBoard(Board gameBoard);
		SDL_Rect makeRect(int posX, int posY, int width, int height);
		void drawRect(enum color pColor);
		int x_offset = (SCREEN_WIDTH - BOARD_WIDTH*BLOCK_SIZE)/2;
		int y_offset = (SCREEN_HEIGHT - BOARD_HEIGHT*BLOCK_SIZE)/2;
		void displayScreenOverlay();
	public:
		IO ();
		void clearScreen(enum color pColor);
		void updateScreen(enum color pColor, Board gameBoard);
		// void drawScreen(int pX1, int pY1, int pX2, int pY2, enum color pColor);
		int getScreenHeight();
		int getScreenWidth();
		void wait(int mseconds);
		SDL_Event sdlEvent;
		SDL_Rect sdlRect;
		void clearEvent();
		unsigned int elapsedTime(Uint32 startTime);
};
#endif

