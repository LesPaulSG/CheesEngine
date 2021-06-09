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

void ChessEngine::Move(int player, sf::Vector2i from, sf::Vector2i to){

}

void ChessEngine::RoundEnd(){

}

void ChessEngine::CheckVictory(){

}

void ChessEngine::draw(sf::RenderWindow* w){
	/*int x, y;
	char s;
	for (int i = 0; i < white.GetNumOfPieces(); ++i) {
		x = white.GetPieces()->at(i)->GetPos().x;
		y = white.GetPieces()->at(i)->GetPos().y;
		s = white.GetPieces()->at(i)->GetSymbol();
		board[x][y] = white.GetPieces()->at(i);
	}

	for (int i = 0; i < black.GetNumOfPieces(); ++i) {
		x = black.GetPieces()->at(i)->GetPos().x;
		y = black.GetPieces()->at(i)->GetPos().y;
		s = black.GetPieces()->at(i)->GetSymbol();
		board[x][y] = black.GetPieces()->at(i);
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] == nullptr) {
				std::cout << 'x';
			}
			else {
				std::cout << board[i][j]->GetSymbol();
			}
		}
		std::cout << std::endl;
	}*/
	white.draw(w);
	black.draw(w);
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
	std::ofstream fout("quickSave.txt", std::ios::out);
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

std::vector<sf::Sprite> ChessEngine::GetPiecesToDraw(){
	std::vector<sf::Sprite> sprites;
	for (auto iter : *white.GetPieces()) {
		sprites.push_back(iter->body);
	}
	for (auto iter : *black.GetPieces()) {
		sprites.push_back(iter->body);
	}
	return sprites;
}

Player* ChessEngine::GetWhite(){
	return &white;
}

Player* ChessEngine::GetBlack(){
	return &black;
}
