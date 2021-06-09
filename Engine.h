#pragma once

#include "Player.h"

class ChessEngine {
private:
	Piece* board[8][8];
	//bool whiteTurn;
	Player white;
	Player black;
	GameState state;


public:
	ChessEngine();

	void Move(int player, sf::Vector2i from, sf::Vector2i to);
	void RoundEnd();
	void CheckVictory();
	void draw(sf::RenderWindow* w);//temp
	void Load(std::string fileName = "startState.txt");
	void Save(std::string fileName = "quickSave.txt");
	std::vector<sf::Sprite> GetPiecesToDraw();
	Player* GetWhite();
	Player* GetBlack();
};