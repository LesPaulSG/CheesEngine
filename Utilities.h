#pragma once

#include <vector>
#include <iostream>
#include <string>

enum GameState {GAME, CHECK, CMATE, STALE};

struct Cell {
	int x;
	int y;
	Cell(int x_, int y_) : x(x_), y(y_) {}
};