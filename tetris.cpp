#include "tetris.hpp"
#include <algorithm>
#include <array>

void Tetromino::rotate() {
	std::array<std::array<int,5>,5> rotatedTetro;
	for (int y = 0; y < tetro.size(); y++) {
		for (int x = 0; x < tetro[0].size(); x++) {
			rotatedTetro[y][x] = tetro[4-x][y];
		}
	}	
	std::swap(tetro, rotatedTetro);
}

char fieldSymbolLegend[] = " ABCDEFG=#";
// TODO translation when printing
int pieces[7][5][5] = 
{
	{
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0},
	},
	{
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	},
	{
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	},
	{
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,1,1,0},
	{0,0,1,1,0},
	{0,0,0,0,0},
	},
	{
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,1,0},
	{0,0,0,1,0},
	{0,0,0,0,0},
	},
	{
	{0,0,0,0,0},
	{0,0,0,1,0},
	{0,0,1,1,0},
	{0,0,1,0,0},
	{0,0,0,0,0},
	},
	{
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	},
};

Tetromino::Tetromino(int piece_number) {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			tetro[y][x] = pieces[piece_number][y][x];
		}
	}
	type = piece_number + 1;
}
