#pragma once

#include "Utilities.h"

enum class fType { PAWN, BSHP, KNHT, ROOK, QUEN, KING, DFLT };

enum class Move { CAN, NOT, KIL };

class Piece {
public:
	Cell pos;
	bool white;
	fType type;
	std::vector<Cell> avaliableMoves;

	Piece(int x, int y, bool white);
	virtual void GenerateMoves() = 0;
	virtual ~Piece() = 0;
};

class Pawn : private Piece {
private:
	//fType Piece::type = PAWN;
	void GenerateMoves() override;
	Pawn(int x, int y, bool white);
};

class Bishop : private Piece {
private:
	//fType Piece::type = BSHP;
	void GenerateMoves() override;
	Bishop(int x, int y, bool white);
};

class Knight : private Piece {
private:
	//fType Piece::type = KNHT;
	void GenerateMoves() override;
	Knight(int x, int y, bool white);
};

class Rook : private Piece {
private:
	//fType Piece::type = ROOK;
	void GenerateMoves() override;
	Rook(int x, int y, bool white);
};

class Queen : private Piece {
private:
	//fType Piece::type = QUEN;
	void GenerateMoves() override;
	Queen(int x, int y, bool white);
};

class King : private Piece {
private:
	//fType Piece::type = KING;
	void GenerateMoves() override;
	King(int x, int y, bool white);
};