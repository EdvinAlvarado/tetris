#ifndef _SCREEN_
#define _SCREEN_
// TODO consider not hardcoding dimensions
// FIXME can go from 5 to 15. cannot do #define BLOCK_SIZE		20 // Width and Height of each block of a piece
#define BLOCK_SIZE		15 // Width and Height of each block of a piece
#define BOARD_WIDTH		28
#define BOARD_HEIGHT	2*BOARD_WIDTH
#define SCREEN_WIDTH 	BOARD_WIDTH*BLOCK_SIZE
#define SCREEN_HEIGHT	BOARD_HEIGHT*BLOCK_SIZE
#endif
