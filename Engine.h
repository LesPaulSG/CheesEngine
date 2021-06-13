#pragma once

#include "Player.h"

class ChessEngine {
private:
	std::vector<std::vector<Piece*>> board;
	std::vector<PieceVis*> boardVis;
	bool whiteTurn = true;
	Player white;
	Player black;
	GameState state;
	Piece* activePiece;
	sf::RectangleShape actPieceLight;
	std::vector<sf::Vector2i> whiteAttackFields;
	std::vector<sf::Vector2i> blackAttackFields;


public:
	ChessEngine();

	void Move(int player, sf::Vector2i from, sf::Vector2i to);
	void RoundEnd();
	void CheckVictory();
	void draw(sf::RenderWindow* w);//temp
	void Load(std::string fileName = "startState.txt");
	void Save(std::string fileName = "quickSave.txt");
	void DeletePiece(Piece* p);
	Player* GetWhite();
	Player* GetBlack();
	void LmbInput(sf::Vector2i clickPos, Player* player);
	Piece* GetActivePiece();
	bool isWhiteTurn();
	std::vector<sf::Vector2i>* GetAttackFields(bool white);
};