#pragma once

#include "Utilities.h"

enum class fType { PAWN = 112, BSHP = 98, KNHT = 107, ROOK = 114, QUEN = 113, KING = 75, DFLT = 0 };

enum class Move { CAN, NOT, KIL };

class Piece {
public:
	Cell pos;
	bool white;
	fType type;
	std::vector<Cell> avaliableMoves;

	Piece(int x, int y, bool white);
	virtual void GenerateMoves() = 0;
	virtual ~Piece() = default;

//public:
	char GetSymbol();
	Cell GetPos();
	
	const std::vector<Cell>* GetAvaliableMoves();
};

class Pawn : public Piece {
private:
	//fType Piece::type = PAWN;

public:
	void GenerateMoves() override;
	Pawn(int x, int y, bool white);
};

class Bishop : public Piece {
private:
	//fType Piece::type = BSHP;

public:
	void GenerateMoves() override;
	Bishop(int x, int y, bool white);
};

class Knight : public Piece {
private:
	//fType Piece::type = KNHT;

public:
	void GenerateMoves() override;
	Knight(int x, int y, bool white);
};

class Rook : public Piece {
private:
	//fType Piece::type = ROOK;

public:
	void GenerateMoves() override;
	Rook(int x, int y, bool white);
};

class Queen : public Piece {
private:
	//fType Piece::type = QUEN;

public:
	void GenerateMoves() override;
	Queen(int x, int y, bool white);
};

class King : public Piece {
private:
	//fType Piece::type = KING;

public:
	void GenerateMoves() override;
	King(int x, int y, bool white);
};