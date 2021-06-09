#pragma once

#include "Piece.h"

class Player{
private:
	bool white;
	bool myMove;
	std::vector<Piece*> pieces;

public:
	Player(bool isWhite);
	void AddPiece(char type, int x, int y);
	const std::vector<Piece*>* GetPieces();
	const int GetNumOfPieces() const;
	void draw(sf::RenderWindow* w);
	bool isWhite();
};