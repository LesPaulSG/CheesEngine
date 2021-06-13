#pragma once

#include "PieceVis.h"

class Player{
private:
	bool white;
	bool myMove;
	std::vector<Piece*> pieces;

public:
	Player(bool isWhite);
	void AddPiece(char type, int x, int y, std::vector<std::vector<Piece*>>& board);
	const std::vector<Piece*>* GetPieces();
	const int GetNumOfPieces() const;
	bool isWhite();
	void DeletePiece(Piece* toDelete);
};