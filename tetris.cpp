#include "tetris.hpp"
#include <algorithm>
#include <array>
#include <iterator>

void Tetromino::rotate() {
	// rotate tetro
	std::array<std::array<int,5>,5> rotatedTetro;
	for (size_t y = 0; y < tetro.size(); y++) {
		for (size_t x = 0; x < tetro[0].size(); x++) {
			rotatedTetro[y][x] = tetro[4-x][y];
		}
	}	
	std::swap(tetro, rotatedTetro);
	// "rotate" dimensions
	std::array<int, 4> t_dim;
	t_dim[0] = pos_delta[3];
	std::copy(pos_delta.begin(), pos_delta.end(), t_dim.begin()+1);
	std::swap(t_dim, pos_delta);
}

// char fieldSymbolLegend[] = " ABCDEFG=#";
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
int dimensions[7][4] = 
{
	{2,0,2,1},
	{1,0,2,2},
	{2,0,1,2},
	{2,2,1,1},
	{2,1,1,1},
	{2,1,1,1},
	{1,1,1,2}
};


Tetromino::Tetromino(int piece_number) {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			tetro[y][x] = pieces[piece_number][y][x];
		}
	}
	type = piece_number + 1;
	std::copy(std::begin(dimensions[piece_number]), std::end(dimensions[piece_number]), std::begin(pos_delta));
}
