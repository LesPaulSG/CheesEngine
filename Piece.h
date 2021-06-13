#pragma once

#include "Utilities.h"

enum class fType { PAWN = 112, BSHP = 98, KNHT = 107, ROOK = 114, QUEN = 113, KING = 75, DFLT = 0 };

enum class Move { CAN, NOT, KIL };

class Piece {
public:
	sf::Vector2i pos;
	bool white;
	bool firstMove = true;
	fType type;
	std::vector<std::vector<Piece*>>* boardPtr;
	std::vector<sf::Vector2i> avaliableMoves;
	std::vector<sf::Vector2i> avaliableAttacks;
	std::vector<sf::Vector2i> movesPattern;
	

	Piece(int x, int y, bool white, std::vector<std::vector<Piece*>>& board);
	Piece(int x, int y, bool white, fType tp);
	virtual void GenerateMoves(int depth);
	virtual ~Piece() = default;

//public:
	char GetSymbol();
	sf::Vector2i GetPos();
	bool CanMoveHere(sf::Vector2i dest);
	bool CanAttackHere(sf::Vector2i dest);
	void Move(sf::Vector2i newPos);

	bool isFieldFree(int x, int y);
	bool isEnemyInField(int x, int y, bool white);
	bool isFieldAvaliable(int x, int y, int depth);
	void ContinuousMoving(int xDir, int yDir, int depth);
	bool ProverkaNaShah(int x, int y, int depth);

	const std::vector<sf::Vector2i>* GetAvaliableMoves();
};

static Piece* whiteKing;
static Piece* blackKing;



class Pawn : public Piece {
private:
	//bool firstMove = true;

public:
	void GenerateMoves(int depth) override;
	Pawn(int x, int y, bool white, std::vector<std::vector<Piece*>>& board);
};

class Bishop : public Piece {
private:
	
public:
	void GenerateMoves(int depth) override;
	Bishop(int x, int y, bool white, std::vector<std::vector<Piece*>>& board);
};

class Knight : public Piece {
private:
	
public:
	void GenerateMoves(int depth) override;
	Knight(int x, int y, bool white, std::vector<std::vector<Piece*>>& board);
};

class Rook : public Piece {
private:
	//bool firstMove = true;

public:
	void GenerateMoves(int depth) override;
	Rook(int x, int y, bool white, std::vector<std::vector<Piece*>>& board);
};

class Queen : public Piece {
private:
	
public:
	void GenerateMoves(int depth) override;
	Queen(int x, int y, bool white, std::vector<std::vector<Piece*>>& board);
};

class King : public Piece {
private:
	//bool firstMove = true;

public:
	void GenerateMoves(int depth) override;
	King(int x, int y, bool white, std::vector<std::vector<Piece*>>& board);
};