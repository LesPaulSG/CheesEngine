#include <fstream>

#include "Engine.h"

const std::string startGameState = "startState";

ChessEngine::ChessEngine() : white(true), black(false) {
	Load(startGameState);
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			board[i][j] = nullptr;
		}
	}
}

void ChessEngine::Move(int player, Cell from, Cell to){

}

void ChessEngine::RoundEnd(){

}

void ChessEngine::CheckVictory(){

}

void ChessEngine::draw(){
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] == nullptr) {
				std::cout << 'x';
			}
		}
		std::cout << std::endl;
	}
}

void ChessEngine::Load(std::string fileName){
	std::ifstream fin;
	fin.open(fileName);

	int num;
	char symbol = 0;
	bool isWhite;
	int x = 0, y = 0;
	std::string line;

	fin >> num;

	for (int i = 0; i < num; ++i) {
		//std::getline(fin, line);
		//symbol	= line[0];
		//isWhite = line[1];
		//x		= line[2];
		//y		= line[3];

		fin >> symbol >> isWhite >> x >> y;

		if (isWhite) {
			switch (symbol)
			{
			case 'x':
				break;
			case 'p':
				//white.AddPiece(Pawn(x, y, isWhite));
				break;
			case 'b':
				//white.AddPiece();
				break;
			case 'k':
				//white.AddPiece();
				break;
			case 'r':
				//white.AddPiece();
				break;
			case 'q':
				//white.AddPiece();
				break;
			case 'K':
				//white.AddPiece();
				break;
			default:
				break;
			}
		}
		else {
			switch (symbol)
			{
			case 'x':
				break;
			case 'p':
				//black.AddPiece();
				break;
			case 'b':
				//black.AddPiece();
				break;
			case 'k':
				//black.AddPiece();
				break;
			case 'r':
				//black.AddPiece();
				break;
			case 'q':
				//black.AddPiece();
				break;
			case 'K':
				//black.AddPiece();
				break;
			default:
				break;
			}
		}
		//int x = i / 8;
		//int y = i % 8;
		//std::cout << x << ' ' << y << std::endl;
	}

	fin.close();
}
