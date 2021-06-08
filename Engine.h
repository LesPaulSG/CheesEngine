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

	void Move(int player, Cell from, Cell to);
	void RoundEnd();
	void CheckVictory();
	void draw();//temp
	void Load(std::string fileName = "startState.txt");
	void Save(std::string fileName = "quickSave.txt");
};