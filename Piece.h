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
	std::vector<sf::Vector2i> avaliableMoves;
	sf::Texture tex;
	sf::Sprite body;
	//sf::CircleShape body;

	Piece(int x, int y, bool white);
	Piece(int x, int y, bool white, fType tp);
	virtual void GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) = 0;
	virtual ~Piece() = default;

//public:
	char GetSymbol();
	sf::Vector2i GetPos();
	void draw(sf::RenderWindow* w);
	bool CanMoveHere(sf::Vector2i dest);
	void Move(sf::Vector2i newPos);
	
	const std::vector<sf::Vector2i>* GetAvaliableMoves();
};

static Piece* whiteKing;
static Piece* blackKing;

bool isFieldFree(std::vector<std::vector<Piece*>>& board, int x, int y);
bool isEnemyInField(std::vector<std::vector<Piece*>>& board, int x, int y, bool white);
void ContinuousMoving(Piece* p, int xDir, int yDir, std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack);
bool ProverkaNaShah(Piece* p, int x, int y, std::vector<std::vector<Piece*>> board);

class Pawn : public Piece {
private:
	//fType Piece::type = PAWN;
	bool firstMove = true;

public:
	void GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) override;
	Pawn(int x, int y, bool white);
};

class Bishop : public Piece {
private:
	//fType Piece::type = BSHP;

public:
	void GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) override;
	Bishop(int x, int y, bool white);
};

class Knight : public Piece {
private:
	//fType Piece::type = KNHT;

public:
	void GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) override;
	Knight(int x, int y, bool white);
};

class Rook : public Piece {
private:
	//fType Piece::type = ROOK;
	bool firstMove = true;

public:
	void GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) override;
	Rook(int x, int y, bool white);
};

class Queen : public Piece {
private:
	//fType Piece::type = QUEN;

public:
	void GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) override;
	Queen(int x, int y, bool white);
};

class King : public Piece {
private:
	//fType Piece::type = KING;
	bool firstMove = true;

public:
	void GenerateMoves(std::vector<std::vector<Piece*>>& board, std::vector<sf::Vector2i>& fieldsUnderAttack) override;
	King(int x, int y, bool white);
};