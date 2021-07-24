#ifndef _IO_
#define _IO_

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include "screen.hpp"
#include "board.hpp"


// one color for each tetromino plus black
// colors 1 thru 7 will be the tetromino colors.
enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, GREY, COLOR_MAX}; 
enum initErrors {INIT_PASS, INIT_ERROR, WINDOW_ERROR, RENDERER_ERROR};

class IO {
	private:
		SDL_Window* sdlWindow;
		SDL_Renderer* sdlRenderer;
		SDL_Color colors[COLOR_MAX];
		int y_offset = (SCREEN_HEIGHT - BOARD_HEIGHT*BLOCK_SIZE)/2;
		int x_offset = (SCREEN_WIDTH - BOARD_WIDTH*BLOCK_SIZE)/2;
		int initGraph();
		void initColors();
		void printBoard(Board gameBoard);
		SDL_Rect makeRect(int posX, int posY, int width, int height);
		void fillRect(enum color pColor);
		void drawRect(enum color pColor);
		void displayScreenOverlay();
		void setRendererColor(enum color pColor);
	public:
		IO ();
		SDL_Event sdlEvent;
		SDL_Rect sdlRect;
		void clearScreen(enum color pColor);
		void updateScreen(enum color pColor, Board gameBoard);
		void wait(int mseconds);
		void clearEvent();
		unsigned int elapsedTime(Uint32 startTime);
};
#endif

