#ifndef _SCREEN_
#define _SCREEN_
// TODO consider not hardcoding dimensions
#define BLOCK_SIZE		15 // Width and Height of each block of a piece
// FIXME BOARD_WIDTH*BOARD_HEIGHT >= 37^2 
#define BOARD_WIDTH		28
#define BOARD_HEIGHT	2*BOARD_WIDTH
// SCREEN_WIDTH and SCREEN_HEIGHT must be equal or greater than BOARD_WIDTH and BOARD_HEIGHT x BLOCK_SIZE
#define SCREEN_WIDTH 	BOARD_WIDTH*BLOCK_SIZE*2
#define SCREEN_HEIGHT	BOARD_HEIGHT*BLOCK_SIZE
#endif
