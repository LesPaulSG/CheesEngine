#pragma once

#include "Piece.h"

class Player{
private:
	bool white;
	bool myMove;
	std::vector<Piece*> pieces;

public:
	Player(bool isWhite);
	void AddPiece(Piece* piece);
};