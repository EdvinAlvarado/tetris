#ifndef _IO_
#define _IO_

#include <SDL2/SDL.h>
#include "screen.hpp"
#include "board.hpp"


// one color for each tetromino plus black
enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; 
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
	public:
		IO ();
		void clearScreen(enum color pColor);
		void updateScreen();
		// void drawScreen(int pX1, int pY1, int pX2, int pY2, enum color pColor);
		int getScreenHeight();
		int getScreenWidth();
		void wait(int mseconds);
		SDL_Event sdlEvent;
		SDL_Rect sdlRect;
};
#endif

