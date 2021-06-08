#include <fstream>

#include "Engine.h"

ChessEngine::ChessEngine() : white(true), black(false) {
	Load();
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			board[i][j] = nullptr;
		}
	}
	Save();
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

void ChessEngine::Load(std::string fileName){// = "satrtState.txt"){
	std::cout << "load" << std::endl;
	std::ifstream fin;
	fin.open(fileName);
	if (!fin.is_open()) {
		std::cout << "not open" << std::endl;
		std::cout << fileName << std::endl;
	}

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
			white.AddPiece(symbol, x, y);
		}
		else {
			black.AddPiece(symbol, x, y);
		}
		//int x = i / 8;
		//int y = i % 8;
		//std::cout << x << ' ' << y << std::endl;
	}

	fin.close();
}

void ChessEngine::Save(std::string fileName){
	std::cout << "save" << std::endl;
	std::fstream fout("quickSave.txt", std::ios::out);
	//fout.open("maybe.txt", std::ios_base::out);
	if (!fout.is_open()) {
		std::cout << "not open" << std::endl;
		std::cout << fileName << std::endl;
	}

	int num = white.GetNumOfPieces() + black.GetNumOfPieces();
	fout << num << std::endl;

	//int x = white.GetPieces()->at(0)->GetPos().x;
	Piece* temp;
	for (int i = 0; i < white.GetNumOfPieces(); ++i){
		temp = white.GetPieces()->at(i);
		fout << temp->GetSymbol() << ' ' << 1 << ' ' << temp->GetPos().x << ' ' << temp->GetPos().y << std::endl;
	}

	for (int i = 0; i < black.GetNumOfPieces(); ++i) {
		temp = black.GetPieces()->at(i);
		fout << temp->GetSymbol() << ' ' << 0 << ' ' << temp->GetPos().x << ' ' << temp->GetPos().y << std::endl;
	}

	fout.close();
}
